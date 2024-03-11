#include "Menu.h"

menu::menu(){play = false;}
menu::~menu()
{
    play = false;
}
bool menu::getPlayState()
{
    return play;
}
void menu::makeMenu(SDL_Renderer *ren)
{
    mainMenu.CreateTexture("Image/menu.png", ren);
}

void menu::Render(SDL_Renderer *ren)
{
    mainMenu.Render(ren);
}

void menu::eventMouse(SDL_Event& ev, Player &p, bool &GameState, bool &MenuState, SDL_Renderer *renderer)
{
    SDL_PollEvent(&ev);
    if(ev.type == SDL_QUIT)
    {
        MenuState = false;
        GameState = false;
    }
    else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.motion.x > 350 && ev.motion.x < 453 && ev.motion.y > 368 && ev.motion.y < 425)//  PLAY BUTTON ///////////////////////////////////
    {
        MenuState = false;
        play = true;

    }
    else if(ev.type == SDL_KEYDOWN) {
        switch (ev.key.keysym.sym)
        {
        case SDLK_1:
            p.CreateTexture("Image/superman.png", renderer);
		    p.CreateTexture1("Image/superman.png", renderer);
		    p.CreateTexture2("Image/superman.png", renderer);
            break;
        case SDLK_2:
            p.CreateTexture("Image/bluebird1.png", renderer);
		    p.CreateTexture1("Image/bluebird2.png", renderer);
		    p.CreateTexture2("Image/bluebird3.png", renderer);
            break;
        case SDLK_3:
            p.CreateTexture("Image/greenbird1.png", renderer);
		    p.CreateTexture1("Image/greenbird2.png", renderer);
		    p.CreateTexture2("Image/greenbird1.png", renderer);
            break;
        case SDLK_4:
            p.CreateTexture("Image/pinkbird1.png", renderer);
		    p.CreateTexture1("Image/pinkbird2.png", renderer);
		    p.CreateTexture2("Image/pinkbird1.png", renderer);
            break;
        case SDLK_5:
            p.CreateTexture("Image/redbird1.png", renderer);
		    p.CreateTexture1("Image/redbird2.png", renderer);
		    p.CreateTexture2("Image/redbird3.png", renderer);
            break;
        case SDLK_6:
            p.CreateTexture("Image/bird1.png", renderer);
		    p.CreateTexture1("Image/bird2.png", renderer);
		    p.CreateTexture2("Image/bird3.png", renderer);
            break;
        default:
            p.CreateTexture("Image/bird1.png", renderer);
		    p.CreateTexture1("Image/bird2.png", renderer);
		    p.CreateTexture2("Image/bird3.png", renderer);
            break;
        }
    }
}

void menu::gameContinue(SDL_Renderer *ren, SDL_Event& e, bool &gameState, bool &MenuState, TextShow score, TextShow maxScore)
{
    endGame.CreateTexture("Image/endGame.png", ren);
    while(1)
    {
        endGame.Render(ren);
        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(e.motion.x > 366 && e.motion.x < 427 && e.motion.y > 350 && e.motion.y < 415){
                break;// TRY AGAIN BUTTON;
            }else if(e.motion.x > 40 && e.motion.x < 130 && e.motion.y > 530 && e.motion.y < 560){
                gameState = false;// EXIT BUTTON
                break;
            }else if(e.motion.x > 10 && e.motion.x < 70 && e.motion.y > 10 && e.motion.y < 70){
                // HOME BUTTON
                MenuState = true;// ERRORRRRRRRR/////////////////
                break;
            }
        }
        else if(e.type == SDL_QUIT ){
            gameState = false;
            //MenuState = false;
            break;
        }
        SDL_RenderClear(ren);
		endGame.Render(ren);
        score.Render(ren, 292, 70);
        //maxScore.Render(ren, 340, 120);
		SDL_RenderPresent(ren);
    }
}

