#include"ScoreText.h"

void TextShow::CreateFont(const char* fileAddress, int size)
{
	font = TTF_OpenFont(fileAddress, size);
	if (!font)
	{
		std::cout << TTF_GetError() << std::endl;
	}
}

void TextShow::Text(std::string Text, SDL_Renderer* ren, SDL_Color color)
{
	SDL_Color black = {0, 0, 0};
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, Text.c_str(), color);
	if (textSurface == NULL)
	{
		std::cout << "Khong tao duoc textSolid" << std::endl;
	}
	fontTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_SizeText(font, Text.c_str(), &srcRest.w, &srcRest.h);
}

void TextShow::setDst(int x, int y)
{
	srcRest.x = 0;
	srcRest.y =  0;
	desRect.x = x; desRect.y = y; desRect.w = srcRest.w; desRect.h = srcRest.h;
}

void TextShow::Render(SDL_Renderer* ren, int x, int y)
{
	TextRect.x = x, TextRect.y = y;
	SDL_QueryTexture(fontTexture, NULL, NULL, &TextRect.w, &TextRect.h);
	SDL_RenderCopy(ren, fontTexture, NULL, &TextRect);
}

void TextShow::RenderAngle(SDL_Renderer* ren, double angle)
{
	SDL_RenderCopyEx(ren, fontTexture, &srcRest, &desRect, angle, NULL, SDL_FLIP_NONE);
}

void TextShow::CloseFont()
{
	TTF_CloseFont(font);
}