#include"ScoreText.h"

void TextShow::CreateFont(const char* fileAddress, int size)
{
	font = TTF_OpenFont(fileAddress, size);
	if (!font)
	{
		std::cout << TTF_GetError() << std::endl;
	}
}

void TextShow::Text(std::string Text, SDL_Renderer* ren)
{
	char* Txt = new char[Text.size() + 1];
	std::copy(Text.begin(), Text.end(), Txt);
	Txt[Text.size()] = '\0';
	SDL_Color color = {242, 242, 242};
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, Txt, color);
	if (textSurface == NULL)
	{
		std::cout << "Khong tao duoc textSolid" << std::endl;
	}
	CreateTexture(textSurface, ren);
	SDL_FreeSurface(textSurface);
	delete Txt;
	Txt = 0;
}

void TextShow::CreateTexture(SDL_Surface* sur, SDL_Renderer* ren)
{
	fontTexture = SDL_CreateTextureFromSurface(ren, sur);
}

void TextShow::Render(SDL_Renderer* ren, int x, int y)
{
	TextRect.x = x, TextRect.y = y;
	SDL_QueryTexture(fontTexture, NULL, NULL, &TextRect.w, &TextRect.h);
	SDL_RenderCopy(ren, fontTexture, NULL, &TextRect);
}

void TextShow::CloseFont()
{
	TTF_CloseFont(font);
}