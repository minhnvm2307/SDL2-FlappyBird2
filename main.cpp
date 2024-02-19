#include <bits/stdc++.h>
#include "include/SDL2/SDL.h"
using namespace std;
typedef long long ll;
#define nl '\n'

struct screen{
    const char *title = "hello world";
    int width = 1366;
    int height = 768;
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    Uint32 window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
} Screen;

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(Screen.title, Screen.x, Screen.y, Screen.width, Screen.height, Screen.window_flags);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, Screen.renderer_flags);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
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