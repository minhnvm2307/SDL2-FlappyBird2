#pragma once
#include"Object.h"

class Player :public Object
{
private:
    double gravity = 0.5;
    //int distance = getDest();
    double Ypos = 256;
    double acceleration = 0;
    bool inJump = false;
    double jumpHeight = -10;
    double jumpTimer;
    double lastJump = 0;
    SDL_Texture* Tex1;
    SDL_Texture* Tex2;
    int animationTimer1;
    int animationTimer2;
public:
    void Gravity();
    void GetJumpTime();
    void Jump();
    void Reset();
    bool JumpState();
    int getYpos();
    void CreateTexture1(const char* address, SDL_Renderer* ren);
    void CreateTexture2(const char* address, SDL_Renderer* ren);
    void Render(SDL_Renderer* ren);
    void RenderUp(SDL_Renderer* ren);
    void RenderDown(SDL_Renderer* ren);
    void RenderDie(SDL_Renderer* ren, double &speed);
};