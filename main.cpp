#include <bits/stdc++.h>
#include "include/SDL2/SDL.h"
using namespace std;
typedef long long ll;
#define nl '\n'

struct screen{
    //title
    const char *title = "SDL2-Template";
    //resolution
    int width = 1280;
    int height = 720;
    //position
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    //window flags
    Uint32 window_fixedsize = 0;
    Uint32 window_resizable = SDL_WINDOW_RESIZABLE;
    //renderer flags
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
} Screen;

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Error: SDL failed to initialize - " << SDL_GetError();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(Screen.title, Screen.x, Screen.y, Screen.width, Screen.height, Screen.window_fixedsize);
    if(!window){
        cout << "Error: Failed to open window - " << SDL_GetError();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, Screen.renderer_flags);
    if(!renderer){
        cout << "Error: Failed to create renderer - " << SDL_GetError();
        return 1;
    }

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

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    return 0;
}