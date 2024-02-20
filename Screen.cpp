#include <bits/stdc++.h>
#include "mylib/screen.hpp"

Screen::Screen() {
    window = SDL_CreateWindow(title, x, y, width, height, fixedsize);

    if (window==NULL){
        std::cout << "Error: Failed to open window - " << SDL_GetError();
    }

    renderer = SDL_CreateRenderer(window, -1, renderer_flags);

    if (renderer==NULL){
        std::cout << "Error: Failed to create renderer - " << SDL_GetError();
    }
}