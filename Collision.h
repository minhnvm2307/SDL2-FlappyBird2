#pragma once
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"

class Collision
{
public:
	static bool CheckCollision(SDL_Rect* A, SDL_Rect* B, int& shield);
	static bool CheckAppleCollision(SDL_Rect* A, SDL_Rect* B);
};