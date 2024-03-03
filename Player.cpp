#include"Player.h"
#include<iostream>

// void Player::RenderDie(SDL_Renderer* ren, double &speed)
// {
// 	speed = 0;
// 	SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), 0, NULL, SDL_FLIP_VERTICAL);
// 	distance-=;
// 	setSource(0, 0, 288, 512);
// 	setDest(distance1, 520, 805, 112);
	
// }

void Player::RenderDown(SDL_Renderer* ren)
{
animationTimer1++;
	if (animationTimer1 < 15)
	{
		SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), 25, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer1 >= 15 && animationTimer1 <= 30)
	{
		SDL_RenderCopyEx(ren, Tex1, &getSrc(), &getDest(), 25, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer1 > 30)
	{
		SDL_RenderCopyEx(ren, Tex2, &getSrc(), &getDest(), 25, NULL, SDL_FLIP_NONE);
	}
	if (animationTimer1 > 45)
	{
		animationTimer1 = 0;
	}}

void Player::RenderUp(SDL_Renderer* ren)
{
animationTimer2++;
	if (animationTimer2 < 15)
	{
		SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), -25, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer2 >= 15 && animationTimer2 <= 30)
	{
		SDL_RenderCopyEx(ren, Tex1, &getSrc(), &getDest(), -25, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer2 > 30)
	{
		SDL_RenderCopyEx(ren, Tex2, &getSrc(), &getDest(), -25, NULL, SDL_FLIP_NONE);
	}
	if (animationTimer2 > 45)
	{
		animationTimer2 = 0;
	}    
}

int Player::getYpos()
{
	return Ypos;
}

void Player::Gravity()
{
    if(JumpState())
    {
        acceleration = acceleration + 0.05;
        jumpHeight = jumpHeight + gravity;
        Ypos = Ypos + gravity + acceleration + jumpHeight;
        setDest(50, Ypos, 55, 38);
        if(jumpHeight > 0)
        {
            inJump = false;
            jumpHeight = -10;
        }
    }
    else
    {
        acceleration = acceleration + 0.05;
        Ypos = Ypos + gravity + acceleration;
        setDest(50, Ypos, 55, 38);  
    }
    Ypos = Ypos + gravity;
    setDest(50, Ypos, 55, 38);
}

void Player::Jump()
{
    acceleration = 0;
    inJump = true;
}

void Player::Reset()
{
	acceleration = 0;
	Ypos = 256;
	lastJump = 0;
}

void Player::GetJumpTime()
{
    jumpTimer = SDL_GetTicks();
}

bool Player::JumpState()
{
    return inJump;
}

void Player::CreateTexture1(const char*address, SDL_Renderer* ren)
{
    Tex1 = TextureManager::Texture(address, ren);
}

void Player::CreateTexture2(const char*address, SDL_Renderer* ren)
{
    Tex2 = TextureManager::Texture(address, ren);
}

