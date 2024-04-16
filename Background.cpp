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

bool Background::Pipe_Above1Update(int incY, int ceil, int &score, double &speed, bool &hard)
{
	this->incY1 = incY;
	this->ceil1 = ceil;
	if(hard) {
		sped3 = 0;
	}
	if (pipeDistance1 <= -100)
	{
		pipeDistance1 += 900;
		height3 = 0;
		score++;
		return true;
	}
	else
	{
		pipeDistance1 -= speed;
		height3 += sped3; 
		if(height3 >= ceil1 || height3<= ceil1-90) sped3*=-1;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance1, -200 + this->incY1 + height3, 52, 400);
		return false;
	}
}

bool Background::Pipe_Below1Update(int incY, int ceil, double &speed, bool &hard)
{
	this->incY1 = incY;
	this->ceil1 = ceil;
	if(hard) {
		sped3 = 0;
	}
	if (pipeDistance1 <= -100)
	{
		pipeDistance1 += 900;
		height3 = 0;
		return true;
	}
	else
	{
		pipeDistance1 -=speed;
		height3 += sped3; 
		if(height3 >= ceil1 || height3<= ceil1-90) sped3*=-1;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance1, 350 + this->incY1 + height3, 52, 400);
		return false;
	}
}

bool Background::Pipe_Above2Update(int incY, int ceil, int &score, double &speed, bool &hard)
{
	this->incY2 = incY;
	this->ceil2 = ceil;
	if(hard) {
		sped2 = 0;
	}
	if (pipeDistance2 <= -100)
	{
		pipeDistance2 += 900;
		height2 = 0;
		score++;
		return true;
	}
	else
	{
		pipeDistance2-=speed;
		height2 += sped2; 
		if(height2 >= ceil2 || height2<= ceil2-90) sped2*=-1;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance2, -200 + this->incY2 + height2, 52, 400);
		return false;
	}
}

bool Background::Pipe_Below2Update(int incY, int ceil, double &speed, bool &hard)
{
	this->incY2 = incY;
	this->ceil2 = ceil;
	if(hard) {
		sped2 = 0;
	}
	if (pipeDistance2 <= -100)
	{
		pipeDistance2 += 900;
		height2 = 0;
		return true;
	}
	else
	{
		pipeDistance2 -= speed;
		height2 += sped2; 
		if(height2 >= ceil2 || height2<= ceil2-90) sped2*=-1;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance2, 350 + this->incY2 + height2, 52, 400);
		return false;
	}
}

bool Background::Pipe_Above3Update(int incY, int ceil, int &score, double &speed, bool &hard)
{
	this->incY3 = incY;
	this->ceil3 = ceil;
	if(hard) {
		sped = 0;
	}
	if (pipeDistance3 <= -100)
	{
		pipeDistance3 += 900;
		pipeDistance3-=speed;
		height = 2;
		score++;
		return true;
	}
	else
	{
		pipeDistance3 -= speed;
		height += sped; 
		if(height >= ceil3 || height<= ceil3-90) sped*=-1;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance3, -200 + this->incY3 + height, 52, 400);
		return false;
	}
}

bool Background::Pipe_Below3Update(int incY, int ceil, double &speed, bool &hard)
{
	this->incY3 = incY;
	this->ceil3 = ceil;
	if(hard) {
		sped = 0;
	}
	if (pipeDistance3 <= -100)
	{
		pipeDistance3 += 900;
		pipeDistance3-=speed;
		height = 0;
		return true;
	}
	else
	{
		pipeDistance3-=speed;
		height += sped; 
		if(height >= ceil3 || height<= ceil3-90) sped*=-1;
		setSource(0, 0, 52, 320);
		setDest(pipeDistance3, 350 + this->incY3 + height, 52, 400);
		return false;
	}
}

bool Background::Golden_AppleUpdate(int incY, double &speed)
{
    this->incY4 = incY;
    if(appleDistance < -100)
    {
        appleDistance += 2650;
        return true;
    }
    else
    {
        appleDistance -= speed;
        setSource(0, 0, 300, 300);
        setDest(appleDistance, 60 + this->incY4 , 45, 45);
        return false;
    }
}

void Background::GroundUpdate1(double &speed)
{
	if (distance1 <= -800)
	{
		distance1 = 805;
	}
	else
	{
		distance1-=5;
		setSource(0, 0, 288, 512);
		setDest(distance1, 520, 805, 115);
	}
}

void Background::GroundUpdate2(double &speed)
{
	if (distance2 <= -800)
	{
		distance2 = 805;
	}
	else
	{
		distance2-=5;
		setSource(0, 0, 288, 512);
		setDest(distance2, 520, 805, 115);
	}
}


double Background::getPipe1Y()
{
	return 300 + this->incY1;
}

double Background::getPipe1X()
{
	return pipeDistance1;
}

double Background::getPipe2Y()
{
	return 300 + this->incY2;
}

double Background::getPipe2X()
{
	return pipeDistance2;
}

double Background::getPipe3Y()
{
	return 300 + this->incY3;
}

double Background::getPipe3X()
{
	return pipeDistance3;
}

double Background::getAppleY()
{
    return 400 + this->incY4;
}

// double Background::getAppleX()
// {
//     return appleDistance;
// }

void Background::Reset()
{
	pipeDistance1 = 400;
	pipeDistance2 = 700;
	pipeDistance3 = 1000;
    appleDistance = 2650;
	ceil1 = 0; ceil2 = 0; ceil3 = 0;
	height2 = 0; height3 = 0; height = 0;
	sped = 1; sped2 =1; sped3 = 1;
	incY1 = 0;
	incY2 = 0;
	incY3 = 0;
    incY4 = 0;
}