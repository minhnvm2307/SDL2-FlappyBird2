#pragma once
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include<iostream>
#include"Object.h"
#include"Player.h"
#include"Background.h"
#include"Collision.h"
#include"ScoreText.h"
#include"Music.h"
using namespace std;

class GameLoop :Background
{
private:
    Player p;
    Background b1;
    Background b2;
    Background ground1,ground2;
	Background Pipe_Above1;
	Background Pipe_Below1;
	Background Pipe_Above2;
	Background Pipe_Below2;
	Background Pipe_Above3;
	Background Pipe_Below3;
    Background Golden_Apple;
    TextShow score;
    TextShow maxScore;
    Sound MusGame;
    const int HEIGHT = 600;
    const int WIDTH = 800;
    bool GameState;
    bool AppleState = true; // trang thai qua tao
    int points = 0;// DIEM GAME
    int maxPoints = 0;
    //int nextCheckPoint = 0;
	int variance1 = rand() % 201 - 100;
	int variance2 = rand() % 201 - 100;
	int variance3 = rand() % 201 - 100;
    int variance4 = rand() % 801 - 300;// Golden Apple
    double FPS = 16.8;
    double accelerate = 0.005;
    SDL_Window* window;
    SDL_Event event1;
    SDL_Renderer* renderer;
    SDL_Texture* player;
    SDL_Texture* background;
    //SDL_Surface * rotozoomSurface()
public:
    GameLoop();
    bool getGameState();
    void Update();
    void Reset();
    void Intialize();
    void Event();
    void CollisionDetection();
    void FPSlimit();
    void Render();
    void Clear();
};
