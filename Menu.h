#pragma once
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "Background.h"
#include "ScoreText.h"
#include "Player.h"


class menu
{
private:
    bool play = false;
    Background mainMenu;
    Background endGame;
    Background choosingBird;
    Background vItem;
public:
    menu();
    ~menu();
    void makeMenu(SDL_Renderer *ren);
    void eventMouse(SDL_Event& ev, Player &p, bool &GameState, bool &MenuState, bool &BirdState, SDL_Renderer *renderer);
    void Render(SDL_Renderer* ren);
    void MakeChoosingBird(SDL_Renderer *ren);
    void RenderChoosingBird(SDL_Renderer* ren);
    void gameContinue(SDL_Renderer *ren, SDL_Event& e, bool &gameState, bool &MenuState, bool &cooldown, TextShow score, TextShow maxScore);
    bool getPlayState();
    void countDown(SDL_Renderer *ren);
};