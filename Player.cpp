#include"Player.h"
#include<iostream>

/// Extra mechanics////////////
void Player::RenderFall(SDL_Renderer* ren)
{
	SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), 90, NULL, SDL_FLIP_NONE);

}

void Player::RenderShield(SDL_Renderer* ren)
{
	SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), ang+=3, NULL, SDL_FLIP_NONE);
	ang%=360;
}
/////////////////////////////

void Player::Render(SDL_Renderer *ren)
{
	angle += 1.4;
	if(angle > 90) angle = 90;
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


void Player::ArmorGravity()
{
    if(JumpState())
    {
        speed = -7;
		angle = -20;
		inJump = false;
    }
	speed += a;
    Ypos += speed;
    setDest(32, Ypos-24, 87, 75);
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

