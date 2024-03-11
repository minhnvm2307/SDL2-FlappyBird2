#include "GameLoop.h"

GameLoop* g = new GameLoop();

int main(int argc, char** argv)
{
    const int FPS = 90;
    const int DELAY_TIME = 1000 / FPS;

    Uint64 frameStart;
    Uint64 frameTime;

    SDL_ShowCursor(SDL_DISABLE);
    g->Intialize();
    
    while(g->getGameState())
    {
        frameStart = SDL_GetTicks();
        if(g->getMenuState()) 
        {
            g->menu();
        }
        g->Event();
        g->Update();
        g->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < DELAY_TIME){
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
    g->Clear();
    return 0;
}



