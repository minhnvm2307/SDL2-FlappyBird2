#pragma once
//#include"GameLoop.h"
#include"textureManager.h"

class Object
{
private:
    SDL_Rect src, dest;
    SDL_Texture* Tex;
public:
    Object();
    SDL_Texture* getTexture();
    SDL_Rect& getSrc();
    SDL_Rect& getDest();
    void setSource(int x, int y, int w, int h);
    void setDest(int x, int y, int w, int h);

    void CreateTexture(const char* address, SDL_Renderer* ren);
    void Render(SDL_Renderer* ren, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest) ;
};