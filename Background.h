#pragma once
#include "Object.h"

class Background :public Object
{
private:
	double distance1 = 0;
	double distance2 = 805;
	double pipeDistance1 = 400;
	double pipeDistance2 = 700;
	double pipeDistance3 = 1000;
    double appleDistance = 2500;
	double incY1 = 0;
	double incY2 = 0;
	double incY3 = 0;
    double incY4 = 0;
    
public:
	bool Pipe_Above1Update(int incY, int &score, double &speed);
	bool Pipe_Below1Update(int incY, double &speed);
	bool Pipe_Above2Update(int incY, int& score, double &speed);
	bool Pipe_Below2Update(int incY, double &speed);
	bool Pipe_Above3Update(int incY, int& score, double &speed);
	bool Pipe_Below3Update(int incY, double &speed);
    bool Golden_AppleUpdate(int incY, double &speed);
    double getAppleX();
    double getAppleY();
	double getPipe1X();
	double getPipe1Y();
	double getPipe2X();
	double getPipe2Y();
	double getPipe3X();
	double getPipe3Y();
	void GroundUpdate1(double &speed);
	void GroundUpdate2(double &speed);
    void Reset();
	void Render(SDL_Renderer* ren);
	void GroundRender(SDL_Renderer* ren);
	void GoldenAppleRender(SDL_Renderer* ren);
	void PipeRender(SDL_Renderer* ren);

};
