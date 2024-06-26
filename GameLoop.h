#pragma once
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include"include/SDL2/SDL_mixer.h"
#include<iostream>
#include"Object.h"
#include"Player.h"
#include"Background.h"
#include"Collision.h"
#include"ScoreText.h"
#include"Menu.h"
using namespace std;

class GameLoop :Background
{
private:
    Player p, p1, p2, armor;
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
    Background cnt1, cnt2, cnt3, ready;
    TextShow score;
    TextShow maxScore;
    menu Main;
    const int HEIGHT = 600;
    const int WIDTH = 800;
    bool GameState;
    bool MenuState = true;
    bool AppleState = true; // trang thai qua tao
    bool cooldownState = false;
    bool BirdState = false;
    bool hard = 1;// DIFFICULTY STATE
    bool pDeath = 0;
    int points = 0;// DIEM GAME
    int maxPoints = 0;
    int shield = 0;
	int variance1 = rand() % 201 - 100;
	int variance2 = rand() % 201 - 100;
	int variance3 = rand() % 201 - 100;
    int variance4 = rand() % 751 - 250;// Golden Apple
    int var1 = rand() % 60 + 30;
	int var2 = rand() % 60 + 30;
	int var3 = rand() % 60 + 30;
    double speed = 2.8;
    Mix_Music *music = NULL;// PLAY BackGround MUSIC
    Mix_Chunk *Jumpsound, *Hitsound, *Getsound;
    SDL_Window* window;
    SDL_Event event1;
    SDL_Renderer* renderer;
    SDL_Texture* player;
    SDL_Texture* background;
    SDL_Color white = {242, 242, 242};
public:
    GameLoop();
    void menu();
    void countDown();
    bool getGameState();
    bool getMenuState();
    void Update();
    void AIflappy();
    double AIpos();
    void Reset();
    void Intialize();
    void Event();
    void CollisionDetection();
    void Render();
    void Clear();
};
