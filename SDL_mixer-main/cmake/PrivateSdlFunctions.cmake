# This file is shared amongst SDL_image/SDL_mixer/SDL_ttf

include(CheckCCompilerFlag)
include(CheckCSourceCompiles)
include(CMakePushCheckState)

macro(sdl_calculate_derived_version_variables MAJOR MINOR MICRO)
    set(SO_VERSION_MAJOR "0")
    set(SO_VERSION_MINOR "${MINOR_VERSION}")
    set(SO_VERSION_MICRO "${MICRO_VERSION}")
    set(SO_VERSION "${SO_VERSION_MAJOR}.${SO_VERSION_MINOR}.${SO_VERSION_MICRO}")

    if(MINOR MATCHES "[02468]$")
        math(EXPR DYLIB_COMPAT_VERSION_MAJOR "100 * ${MINOR} + 1")
        set(DYLIB_COMPAT_VERSION_MINOR "0")
        math(EXPR DYLIB_CURRENT_VERSION_MAJOR "${DYLIB_COMPAT_VERSION_MAJOR}")
        set(DYLIB_CURRENT_VERSION_MINOR "${MICRO}")
    else()
        math(EXPR DYLIB_COMPAT_VERSION_MAJOR "100 * ${MINOR} + ${MICRO} + 1")
        set(DYLIB_COMPAT_VERSION_MINOR "0")
        math(EXPR DYLIB_CURRENT_VERSION_MAJOR "${DYLIB_COMPAT_VERSION_MAJOR}")
        set(DYLIB_CURRENT_VERSION_MINOR "0")
    endif()
    set(DYLIB_COMPAT_VERSION_MICRO "0")
    set(DYLIB_CURRENT_VERSION_MICRO "0")

    set(DYLIB_CURRENT_VERSION "${DYLIB_CURRENT_VERSION_MAJOR}.${DYLIB_CURRENT_VERSION_MINOR}.${DYLIB_CURRENT_VERSION_MICRO}")
    set(DYLIB_COMPAT_VERSION "${DYLIB_COMPAT_VERSION_MAJOR}.${DYLIB_COMPAT_VERSION_MINOR}.${DYLIB_COMPAT_VERSION_MICRO}")
endmacro()

function(read_absolute_symlink DEST PATH)
    file(READ_SYMLINK "${PATH}" p)
    if(NOT IS_ABSOLUTE "${p}")
        get_filename_component(pdir "${PATH}" DIRECTORY)
        set(p "${pdir}/${p}")
    endif()
    get_filename_component(p "${p}" ABSOLUTE)
    set("${DEST}" "${p}" PARENT_SCOPE)
endfunction()

function(win32_implib_identify_dll DEST IMPLIB)
    cmake_parse_arguments(ARGS "NOTFATAL" "" "" ${ARGN})
    if(CMAKE_DLLTOOL)
        execute_process(
            COMMAND "${CMAKE_DLLTOOL}" --identify "${IMPLIB}"
            RESULT_VARIABLE retcode
            OUTPUT_VARIABLE stdout
            ERROR_VARIABLE stderr)
        if(NOT retcode EQUAL 0)
            if(NOT ARGS_NOTFATAL)
                message(FATAL_ERROR "${CMAKE_DLLTOOL} failed.")
            else()
                set("${DEST}" "${DEST}-NOTFOUND" PARENT_SCOPE)
                return()
            endif()
        endif()
        string(STRIP "${stdout}" result)
        set(${DEST} "${result}" PARENT_SCOPE)
    elseif(MSVC)
        get_filename_component(CMAKE_C_COMPILER_DIRECTORY "${CMAKE_C_COMPILER}" DIRECTORY CACHE)
        find_program(CMAKE_DUMPBIN NAMES dumpbin PATHS "${CMAKE_C_COMPILER_DIRECTORY}")
        if(CMAKE_DUMPBIN)
            execute_process(
                COMMAND "${CMAKE_DUMPBIN}" "-headers" "${IMPLIB}"
                RESULT_VARIABLE retcode
                OUTPUT_VARIABLE stdout
                ERROR_VARIABLE stderr)
            if(NOT retcode EQUAL 0)
                if(NOT ARGS_NOTFATAL)
                    message(FATAL_ERROR "dumpbin failed.")
                else()
                    set(${DEST} "${DEST}-NOTFOUND" PARENT_SCOPE)
                    return()
                endif()
            endif()
            string(REGEX MATCH "DLL name[ ]+:[ ]+([^\n]+)\n" match "${stdout}")
            if(NOT match)
                if(NOT ARGS_NOTFATAL)
                    message(FATAL_ERROR "dumpbin did not find any associated dll for ${IMPLIB}.")
                else()
                    set(${DEST} "${DEST}-NOTFOUND" PARENT_SCOPE)
                    return()
                endif()
            endif()
            set(result "${CMAKE_MATCH_1}")
            set(${DEST} "${result}" PARENT_SCOPE)
        else()
            message(FATAL_ERROR "Cannot find dumpbin, please set CMAKE_DUMPBIN cmake variable")
        endif()
    else()
        if(NOT ARGS_NOTFATAL)
            message(FATAL_ERROR "Don't know how to identify dll from import library. Set CMAKE_DLLTOOL (for mingw) or CMAKE_DUMPBIN (for MSVC)")
        else()
            set(${DEST} "${DEST}-NOTFOUND")
        endif()
    endif()
endfunction()

function(get_actual_target)
    set(dst "${ARGV0}")
    set(target "${${dst}}")
    set(input "${target}")
    get_target_property(alias "${target}" ALIASED_TARGET)
    while(alias)
        set(target "${alias}")
        get_target_property(alias "${target}" ALIASED_TARGET)
    endwhile()
    message(DEBUG "get_actual_target(\"${input}\") -> \"${target}\"")
    set("${dst}" "${target}" PARENT_SCOPE)
endfunction()

function(target_get_dynamic_library DEST TARGET)
    set(result)
    get_actual_target(TARGET)
    if(WIN32)
        # Use the target dll of the import library
        set(props_to_check IMPORTED_IMPLIB)
        if(CMAKE_BUILD_TYPE)
            list(APPEND props_to_check IMPORTED_IMPLIB_${CMAKE_BUILD_TYPE})
        endif()
        list(APPEND props_to_check IMPORTED_LOCATION)
        if(CMAKE_BUILD_TYPE)
            list(APPEND props_to_check IMPORTED_LOCATION_${CMAKE_BUILD_TYPE})
        endif()
        foreach (config_type ${CMAKE_CONFIGURATION_TYPES} RELEASE DEBUG RELWITHDEBINFO MINSIZEREL)
            list(APPEND props_to_check IMPORTED_IMPLIB_${config_type})
            list(APPEND props_to_check IMPORTED_LOCATION_${config_type})
        endforeach()

        foreach(prop_to_check ${props_to_check})
            if(NOT result)
                get_target_property(propvalue "${TARGET}" ${prop_to_check})
                if(propvalue AND EXISTS "${propvalue}")
                    win32_implib_identify_dll(result "${propvalue}" NOTFATAL)
                endif()
            endif()
        endforeach()
    else()
        # 1. find the target library a file might be symbolic linking to
        # 2. find all other files in the same folder that symolic link to it
        # 3. sort all these files, and select the 1st item on Linux, and last on Macos
        set(location_properties IMPORTED_LOCATION)
        if(CMAKE_BUILD_TYPE)
            list(APPEND location_properties IMPORTED_LOCATION_${CMAKE_BUILD_TYPE})
        endif()
        foreach (config_type ${CMAKE_CONFIGURATION_TYPES} RELEASE DEBUG RELWITHDEBINFO MINSIZEREL)
            list(APPEND location_properties IMPORTED_LOCATION_${config_type})
        endforeach()
        if(APPLE)
            set(valid_shared_library_regex "\\.[0-9]+\\.dylib$")
        else()
            set(valid_shared_library_regex "\\.so\\.([0-9.]+)?[0-9]")
        endif()
        foreach(location_property ${location_properties})
            if(NOT result)
                get_target_property(library_path "${TARGET}" ${location_property})
                message(DEBUG "get_target_property(${TARGET} ${location_propert}) -> ${library_path}")
                if(EXISTS "${library_path}")
                    get_filename_component(library_path "${library_path}" ABSOLUTE)
                    while (IS_SYMLINK "${library_path}")
                        read_absolute_symlink(library_path "${library_path}")
                    endwhile()
                    message(DEBUG "${TARGET} -> ${library_path}")
                    get_filename_component(libdir "${library_path}" DIRECTORY)
                    file(GLOB subfiles "${libdir}/*")
                    set(similar_files "${library_path}")
                    foreach(subfile ${subfiles})
                        if(IS_SYMLINK "${subfile}")
                            read_absolute_symlink(subfile_target "${subfile}")
                            while(IS_SYMLINK "${subfile_target}")
                                read_absolute_symlink(subfile_target "${subfile_target}")
                            endwhile()
                            get_filename_component(subfile_target "${subfile_target}" ABSOLUTE)
                            if(subfile_target STREQUAL library_path AND subfile MATCHES "${valid_shared_library_regex}")
                                list(APPEND similar_files "${subfile}")
                            endif()
                        endif()
                    endforeach()
                    list(SORT similar_files)
                    message(DEBUG "files that are similar to \"${library_path}\"=${similar_files}")
                    if(APPLE)
                        list(REVERSE similar_files)
                    endif()
                    list(GET similar_files 0 item)
                    get_filename_component(result "${item}" NAME)
                endif()
            endif()
        endforeach()
    endif()
    if(result)
        string(TOLOWER "${result}" result_lower)
        if(WIN32 OR OS2)
            if(NOT result_lower MATCHES ".*dll")
                message(FATAL_ERROR "\"${result}\" is not a .dll library")
            endif()
        elseif(APPLE)
            if(NOT result_lower MATCHES ".*dylib.*")
                message(FATAL_ERROR "\"${result}\" is not a .dylib shared library")
            endif()
        else()
            if(NOT result_lower MATCHES ".*so.*")
                message(FATAL_ERROR "\"${result}\" is not a .so shared library")
            endif()
        endif()
    else()
        get_target_property(target_type ${TARGET} TYPE)
        if(target_type MATCHES "SHARED_LIBRARY|MODULE_LIBRARY")
            # OK
        elseif(target_type MATCHES "STATIC_LIBRARY|OBJECT_LIBRARY|INTERFACE_LIBRARY|EXECUTABLE")
            message(SEND_ERROR "${TARGET} is not a shared library, but has type=${target_type}")
        else()
            message(WARNING "Unable to extract dynamic library from target=${TARGET}, type=${target_type}.")
        endif()
        # TARGET_SONAME_FILE is not allowed for DLL target platforms.
        if(WIN32)
          set(result "$<TARGET_FILE_NAME:${TARGET}>")
        else()
          set(result "$<TARGET_SONAME_FILE_NAME:${TARGET}>")
        endif()
    endif()
    set(${DEST} ${result} PARENT_SCOPE)
endfunction()

function(sdl_check_project_in_subfolder relative_subfolder name vendored_option)
    cmake_parse_arguments(ARG "" "FILE" "" ${ARGN})
    if(NOT ARG_FILE)
        set(ARG_FILE "CMakeLists.txt")
    endif()
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/${relative_subfolder}/${ARG_FILE}")
        message(FATAL_ERROR "Could not find ${ARG_FILE} for ${name} in ${relative_subfolder}.\n"
            "Run the download script in the external folder, or re-configure with -D${vendored_option}=OFF to use system packages.")
    endif()
endfunction()

macro(sdl_check_linker_flag flag var)
    # FIXME: Use CheckLinkerFlag module once cmake minimum version >= 3.18
    cmake_push_check_state(RESET)
    set(CMAKE_REQUIRED_LINK_OPTIONS "${flag}")
    check_c_source_compiles("int main() { return 0; }" ${var} FAIL_REGEX "(unsupported|syntax error|unrecognized option)")
    cmake_pop_check_state()
endmacro()

function(SDL_detect_linker)
    if(CMAKE_VERSION VERSION_LESS 3.29)
        if(NOT DEFINED SDL_CMAKE_C_COMPILER_LINKER_ID)
            execute_process(COMMAND ${CMAKE_LINKER} -v OUTPUT_VARIABLE LINKER_OUTPUT ERROR_VARIABLE LINKER_OUTPUT)
            string(REGEX REPLACE "[\r\n]" " " LINKER_OUTPUT "${LINKER_OUTPUT}")
            if(LINKER_OUTPUT MATCHES ".*Microsoft.*")
                set(linker MSVC)
            else()
                set(linker GNUlike)
            endif()
            message(STATUS "Linker identification: ${linker}")
            set(SDL_CMAKE_C_COMPILER_LINKER_ID "${linker}" CACHE STRING "Linker identification")
            mark_as_advanced(SDL_CMAKE_C_COMPILER_LINKER_ID)
        endif()
        set(CMAKE_C_COMPILER_LINKER_ID "${SDL_CMAKE_C_COMPILER_LINKER_ID}" PARENT_SCOPE)
    endif()
endfunction()

function(check_linker_support_version_script VAR)
    SDL_detect_linker()
    if(CMAKE_C_COMPILER_LINKER_ID MATCHES "^(MSVC)$")
        set(LINKER_SUPPORTS_VERSION_SCRIPT FALSE)
    else()
        cmake_push_check_state(RESET)
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dummy.sym" "n_0 {\n global:\n  func;\n local: *;\n};\n")
        list(APPEND CMAKE_REQUIRED_LINK_OPTIONS "-Wl,--version-script=${CMAKE_CURRENT_BINARY_DIR}/dummy.sym")
        check_c_source_compiles("int func(void) {return 0;} int main(int argc,char*argv[]){(void)argc;(void)argv;return func();}" LINKER_SUPPORTS_VERSION_SCRIPT FAIL_REGEX "(unsupported|syntax error|unrecognized option)")
        cmake_pop_check_state()
    endif()
    set(${VAR} "${LINKER_SUPPORTS_VERSION_SCRIPT}" PARENT_SCOPE)
endfunction()

function(sdl_target_link_options_no_undefined TARGET)
    if(NOT MSVC)
        if(CMAKE_C_COMPILER_ID MATCHES "AppleClang")
            target_link_options(${TARGET} PRIVATE "-Wl,-undefined,error")
        else()
            sdl_check_linker_flag("-Wl,--no-undefined" HAVE_WL_NO_UNDEFINED)
            if(HAVE_WL_NO_UNDEFINED AND NOT ((CMAKE_C_COMPILER_ID MATCHES "Clang") AND WIN32))
                target_link_options(${TARGET} PRIVATE "-Wl,--no-undefined")
            endif()
        endif()
    endif()
endfunction()

function(sdl_target_link_option_version_file TARGET VERSION_SCRIPT)
    check_linker_support_version_script(HAVE_WL_VERSION_SCRIPT)
    if(HAVE_WL_VERSION_SCRIPT)
        target_link_options(${TARGET} PRIVATE "-Wl,--version-script=${VERSION_SCRIPT}")
    else()
        if(LINUX OR ANDROID)
            message(FATAL_ERROR "Linker does not support '-Wl,--version-script=xxx.sym'. This is required on the current host platform.")
        endif()
    endif()
endfunction()

function(sdl_add_warning_options TARGET)
    cmake_parse_arguments(ARGS "" "WARNING_AS_ERROR" "" ${ARGN})
    if(MSVC)
        target_compile_options(${TARGET} PRIVATE /W2)
    else()
        target_compile_options(${TARGET} PRIVATE -Wall -Wextra)
    endif()
    if(ARGS_WARNING_AS_ERROR)
        if(MSVC)
            target_compile_options(${TARGET} PRIVATE /WX)
        else()
            target_compile_options(${TARGET} PRIVATE -Werror)
        endif()
    endif()
endfunction()

function(sdl_no_deprecated_errors TARGET)
    check_c_compiler_flag(-Wno-error=deprecated-declarations HAVE_WNO_ERROR_DEPRECATED_DECLARATIONS)
        if(HAVE_WNO_ERROR_DEPRECATED_DECLARATIONS)
    target_compile_options(${TARGET} PRIVATE "-Wno-error=deprecated-declarations")
endif()
endfunction()

function(sdl_get_git_revision_hash VARNAME)
    set("${VARNAME}" "" CACHE STRING "${PROJECT_NAME} revision")
    set(revision "${${VARNAME}}")
    if(NOT revision)
      if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt")
        # If VERSION.txt exists, it contains the SDL version
        file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" revision_version)
        string(STRIP "${revision_version}" revision_version)
      else()
        # If VERSION.txt does not exist, use git to calculate a version
        git_describe(revision_version)
        if(NOT revision_version)
          set(revision_version "${PROJECT_VERSION}-no-vcs")
        endif()
      endif()
      set(revision "${revision_version}")
    endif()
    set("${VARNAME}" "${revision}" PARENT_SCOPE)
endfunction()
