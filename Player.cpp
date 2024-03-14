#include"Player.h"
#include<iostream>

/// old mechanics////////////
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
/////////////////////////////

void Player::Render(SDL_Renderer *ren)
{
	angle += 1.1;
	if(angle > 30) angle = 30;
	if(speed < 0){
		SDL_RenderCopyEx(ren, Tex2, &getSrc(), &getDest(), -30, NULL, SDL_FLIP_NONE);// flying
	}else{
		SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);// failing
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
        speed = -7;
		angle = -20;
		inJump = false;
    }
	speed += a;
    Ypos += speed;
    setDest(50, Ypos, 52, 33);
}

void Player::Jump()
{
    inJump = true;
}

void Player::Reset()
{
	Ypos = 256;
	speed = -7;
	angle = -20;
}

bool Player::JumpState()
{
    return inJump;
}

void Player::CreateTexture1(const char*address, SDL_Renderer* ren)
{
    Tex1 = TextureManager::Texture(address, ren);// vertical flying
}

void Player::CreateTexture2(const char*address, SDL_Renderer* ren)
{
    Tex2 = TextureManager::Texture(address, ren);// flying up
}

