#pragma once
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"

class TextureManager
{
public:
    static SDL_Texture* Texture(const char* filelocation, SDL_Renderer* ren);
};
