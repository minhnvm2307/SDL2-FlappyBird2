#pragma once
#include "include/SDL2/SDL_ttf.h"
#include<string>
#include<iostream>

class TextShow
{
private:
    TTF_Font* font;
    SDL_Rect TextRect;
    SDL_Texture* fontTexture;
public:
    void CreateFont(const char* fileAddress, int size);
	void Text(std::string Text, SDL_Renderer* ren);
	void CreateTexture(SDL_Surface* sur, SDL_Renderer* ren);
	void Render(SDL_Renderer* ren, int x, int y);
	void CloseFont();
};
