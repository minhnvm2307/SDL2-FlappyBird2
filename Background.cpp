#include "Background.h"
#include<cstdlib>

void Background::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), NULL, NULL);
}

void Background::GoldenAppleRender(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Background::GroundRender(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Background::PipeRender(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

// bool Background::Apple_Eaten()
// {
//     return eat;
// }

// void Background::SetEat(bool &eat)
// {
//     Background::eat = true;
// }

bool Background::Pipe_Above1Update(int incY, int &score)
{
	this->incY1 = incY;
	if (pipeDistance1 <= -100)
	{
		pipeDistance1 += 900;
		score++;
		return true;
	}
	else
	{
		pipeDistance1-=3;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance1, -200 + this->incY1, 52, 400);
		return false;
	}
}

bool Background::Pipe_Below1Update(int incY)
{
	this->incY1 = incY;
	if (pipeDistance1 <= -100)
	{
		pipeDistance1 += 900;
		return true;
	}
	else
	{
		pipeDistance1 -=3;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance1, 350 + this->incY1, 52, 400);
		return false;
	}
}

bool Background::Pipe_Above2Update(int incY, int &score)
{
	this->incY2 = incY;
	if (pipeDistance2 <= -100)
	{
		pipeDistance2 += 900;
		score++;
		return true;
	}
	else
	{
		pipeDistance2-=3;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance2, -200 + this->incY2, 52, 400);
		return false;
	}
}

bool Background::Pipe_Below2Update(int incY)
{
	this->incY2 = incY;
	if (pipeDistance2 <= -100)
	{
		pipeDistance2 += 900;
		return true;
	}
	else
	{
		pipeDistance2-=3;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance2, 350 + this->incY2, 52, 400);
		return false;
	}
}

bool Background::Pipe_Above3Update(int incY, int &score)
{
	this->incY3 = incY;
	if (pipeDistance3 <= -100)
	{
		pipeDistance3 += 900;
		pipeDistance3-=3;
		score++;
		return true;
	}
	else
	{
		pipeDistance3-=3;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance3, -200 + this->incY3, 52, 400);
		return false;
	}
}

bool Background::Pipe_Below3Update(int incY)
{
	this->incY3 = incY;
	if (pipeDistance3 <= -100)
	{
		pipeDistance3 += 900;
		pipeDistance3-=3;
		return true;
	}
	else
	{
		pipeDistance3-=3;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance3, 350 + this->incY3, 52, 400);
		return false;
	}
}

bool Background::Golden_AppleUpdate(int incY, int& score)
{
    this->incY4 = incY;
    if(appleDistance < -100)
    {
        appleDistance += 3345;
        score += 5;
        return true;
    }
    else
    {
        appleDistance -= 3;
        setSource(0, 0, 300, 300);
        setDest(appleDistance, 60 + this->incY4 , 45, 45);
        return false;
    }
}

void Background::GroundUpdate1()
{
	if (distance1 <= -800)
	{
		distance1 = 805;
	}
	else
	{
		distance1-=3;
		setSource(0, 0, 288, 512);
		setDest(distance1, 520, 805, 112);
	}
}

void Background::GroundUpdate2()
{
	if (distance2 <= -800)
	{
		distance2 = 805;
	}
	else
	{
		distance2-=3;
		setSource(0, 0, 288, 512);
		setDest(distance2, 520, 805, 112);
	}
}


int Background::getPipe1Y()
{
	return 300 + this->incY1;
}

int Background::getPipe1X()
{
	return pipeDistance1;
}

int Background::getPipe2Y()
{
	return 300 + this->incY2;
}

int Background::getPipe2X()
{
	return pipeDistance2;
}

int Background::getPipe3Y()
{
	return 300 + this->incY3;
}

int Background::getPipe3X()
{
	return pipeDistance3;
}

int Background::getAppleY()
{
    return 400 + this->incY4;
}

int Background::getAppleX()
{
    return appleDistance;
}

void Background::Reset()
{
	pipeDistance1 = 400;
	pipeDistance2 = 700;
	pipeDistance3 = 1000;
    appleDistance = 2000;
	incY1 = 0;
	incY2 = 0;
	incY3 = 0;
    incY4 = 0;
}