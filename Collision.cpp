#include "Collision.h"

bool Collision::CheckCollision(SDL_Rect* A, SDL_Rect* B, int& shield)
{
	SDL_bool Collision = SDL_HasIntersection(A, B);
	if (Collision && shield == 0)
	{
		return true;
	}
	else{
		return false;
	}
}

bool Collision::CheckAppleCollision(SDL_Rect* A, SDL_Rect* B)
{
	SDL_bool Collision = SDL_HasIntersection(A, B);
	if (Collision)
	{
		return true;
	}
	else
		return false;
}