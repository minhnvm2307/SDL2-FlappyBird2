#pragma once
#include "include/SDL2/SDL_ttf.h"
#include<string>
#include<iostream>

class TextShow
{
private:
    TTF_Font* font;
    SDL_Rect TextRect, srcRest, desRect;
    SDL_Texture* fontTexture;
public:
    void CreateFont(const char* fileAddress, int size);
	void Text(std::string Text, SDL_Renderer* ren, SDL_Color color);
    void setDst(int x, int y);
	void Render(SDL_Renderer* ren, int x, int y);
    void RenderAngle(SDL_Renderer* ren, double angle);
	void CloseFont();
};
