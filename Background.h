#pragma once
#include "Object.h"
#include<iostream>

class Background :public Object
{
private:
	double distance1 = 0;
	double distance2 = 805;
	double height = 0; int sped = 1;// pipe 3
	double height3 = 0; int sped3 = 1;// pipe1
	double height2 = 0; int sped2 = 1;// pipe 2
	int ceil1 = 0, ceil2 = 0, ceil3 = 0;
	double pipeDistance1 = 400;
	double pipeDistance2 = 700;
	double pipeDistance3 = 1000;
    double appleDistance = 2650;
	double incY1 = 0;
	double incY2 = 0;
	double incY3 = 0;
    double incY4 = 0;
    
public:
	bool Pipe_Above1Update(int incY, int ceil, int &score, double &speed, bool &hard);
	bool Pipe_Below1Update(int incY, int ceil, double &speed, bool &hard);
	bool Pipe_Above2Update(int incY, int ceil, int& score, double &speed, bool &hard);
	bool Pipe_Below2Update(int incY, int ceil, double &speed, bool &hard);
	bool Pipe_Above3Update(int incY, int ceil, int& score, double &speed, bool &hard);
	bool Pipe_Below3Update(int incY, int ceil, double &speed, bool &hard);
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
