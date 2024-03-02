#include "GameLoop.h"

GameLoop* g = new GameLoop();

int main(int argc, char** argv)
{
    double first, last = 0;
    g->Intialize();
    while(g->getGameState())
    {
        g->Event();
        g->Update();
        g->Render();
        g->FPSlimit();
    }
    g->Clear();
    return 0;
}
