#pragma once
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_mixer.h"
#include "Background.h"
#include "ScoreText.h"
#include "Player.h"
#include <bits/stdc++.h>

using namespace std;


class menu 
{
private:
    bool play = false;
    Background mainMenu;
    Background endGame;
    Background choosingBird, tutorial;
    Background vItem;
    Background settingItem, settingMenu, leaderB;
    TextShow DifficultyState;
    TextShow Bmusic;
    TextShow point, maxPoint, newRecord;
    bool settingState = 0;
    bool tutorState = 0;
    bool musicState = 1;
    int count = 0; int prevMaxPoint = 0;
    std::string Diff1 = "Difficult", Diff2 = "Easy", On = "ON", Off = "OFF";
    bool ptrHard = 1;
    SDL_Color blue = {113, 178, 252} , red = {245, 80, 124}, white = {252, 252, 252};

    //////LEADER BOARD
    vector<string> saveScore, saveMode;
    vector<TextShow> saveRen;
    bool leaderState = 0;
public:
    menu();
    ~menu();
    void makeMenu(SDL_Renderer *ren);
    void eventMouse(SDL_Event& ev, Player &p, bool &GameState, bool &MenuState, bool &BirdState, bool &hard, SDL_Renderer *renderer);
    void Render(SDL_Renderer* ren);
    void MakeChoosingBird(SDL_Renderer *ren);
    void RenderChoosingBird(SDL_Renderer* ren);
    void makeSetting(SDL_Renderer *ren);
    void gameContinue(SDL_Renderer *ren, SDL_Event& e, bool &gameState, bool &MenuState, bool &cooldown, int score, int maxScore);
    bool getPlayState();
    void leaderBoard(SDL_Renderer *ren);
    void upDateBoard(int score, SDL_Renderer* ren);
    void closeLeaderBoard();
};