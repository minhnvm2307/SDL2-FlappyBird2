#pragma once
#include <bits/stdc++.h>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"

class Screen{
public:
    Screen();

    //title
    const char * title = "SDL2-Template";

    //resolution
    int width = 1280;
    int height = 720;

    //position
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;

    //window flags
    Uint32 fixedsize = 0;
    Uint32 resizable = SDL_WINDOW_RESIZABLE;

    //renderer flags
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    //other properties
    bool isFullscreen = false;
    bool isMaximized = false;
    bool isResizable = false;

    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

};