#include <bits/stdc++.h>
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_mixer.h"
#include "include/SDL2/SDL_ttf.h"
#include "mylib/Screen.hpp"

int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Error: SDL failed to initialize - " << SDL_GetError();
        return 1;
    }

    Screen current;

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }
    }
    return 0;
}