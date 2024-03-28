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

void menu::MakeChoosingBird(SDL_Renderer* ren)
{
    choosingBird.CreateTexture("Image/choosingBird.png", ren);
    vItem.CreateTexture("Image/vItem.png", ren);
    vItem.setSource(0, 0, 360, 360);
    vItem.setDest(290, 320, 55, 55);
    choosingBird.setSource(0, 0, 500, 300);
    choosingBird.setDest(150, 250, 500, 300);
}

void menu::RenderChoosingBird(SDL_Renderer *ren)
{
    choosingBird.GroundRender(ren);
    vItem.GroundRender(ren);
}


void menu::eventMouse(SDL_Event& ev, Player &p, bool &GameState, bool &MenuState, bool &BirdState, SDL_Renderer *renderer)
{
    SDL_PollEvent(&ev);
    if(ev.type == SDL_QUIT)
    {
        MenuState = false;
        GameState = false;
        play = true;
    }
    if(ev.type == SDL_MOUSEBUTTONDOWN){
        if(ev.motion.x > 350 && ev.motion.x < 453 && ev.motion.y > 368 && ev.motion.y < 425 && BirdState==false)//  PLAY BUTTON 
        {
            MenuState = false;
            play = true;

        }
        else if(ev.motion.x > 350 && ev.motion.x < 453 && ev.motion.y > 440 && ev.motion.y < 475)//OPEN MENU BIRD
        {
            BirdState = true;
        }
        else if(ev.motion.x > 150 && ev.motion.x < 190 && ev.motion.y > 260 && ev.motion.y < 290)//CLOSE MENU BIRD
        {
            BirdState = false;
        }
    
        if(BirdState == true) {
            if(ev.motion.x > 485 && ev.motion.x < 610 && ev.motion.y > 340 && ev.motion.y < 420){
                vItem.setDest(570, 320, 55, 55);
                p.CreateTexture("Image/superbird.png", renderer);
                p.CreateTexture1("Image/superbird.png", renderer);
                p.CreateTexture2("Image/superbird.png", renderer);
            }
            else if(ev.motion.x > 340 && ev.motion.x < 480 && ev.motion.y > 430 && ev.motion.y < 515){
                vItem.setDest(430, 410, 55, 55);
                p.CreateTexture("Image/bluebird1.png", renderer);
                p.CreateTexture1("Image/bluebird2.png", renderer);
                p.CreateTexture2("Image/bluebird3.png", renderer);
            }
            else if(ev.motion.x > 485 && ev.motion.x < 610 && ev.motion.y > 430 && ev.motion.y < 515){
                vItem.setDest(570, 410, 55, 55);
                p.CreateTexture("Image/greenbird1.png", renderer);
                p.CreateTexture1("Image/greenbird2.png", renderer);
                p.CreateTexture2("Image/greenbird2.png", renderer);
            }
            else if(ev.motion.x > 200 && ev.motion.x < 330 && ev.motion.y > 430 && ev.motion.y < 515){
                vItem.setDest(290, 410, 55, 55);
                p.CreateTexture("Image/pinkbird1.png", renderer);
                p.CreateTexture1("Image/pinkbird2.png", renderer);
                p.CreateTexture2("Image/pinkbird2.png", renderer);
            }
            else if(ev.motion.x > 340 && ev.motion.x < 480 && ev.motion.y > 340 && ev.motion.y < 420){
                vItem.setDest(430, 320, 55, 55);
                p.CreateTexture("Image/redbird1.png", renderer);
                p.CreateTexture1("Image/redbird2.png", renderer);
                p.CreateTexture2("Image/redbird3.png", renderer);
            }
            else if(ev.motion.x > 200 && ev.motion.x < 330 && ev.motion.y > 340 && ev.motion.y < 420){
                vItem.setDest(290, 320, 55, 55);
                p.CreateTexture("Image/bird1.png", renderer);
                p.CreateTexture1("Image/bird2.png", renderer);
                p.CreateTexture2("Image/bird3.png", renderer);
            }
        }
    }
}

void menu::gameContinue(SDL_Renderer *ren, SDL_Event& e, bool &gameState, bool &MenuState, bool &cooldown, TextShow score, TextShow maxScore)
{
    endGame.CreateTexture("Image/endGame.png", ren);

    while(1)
    {
        SDL_RenderClear(ren);
		endGame.Render(ren);
        //score.Render(ren, 292, 70);
        maxScore.Render(ren, 320, 120);
		SDL_RenderPresent(ren);

        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(e.motion.x > 366 && e.motion.x < 427 && e.motion.y > 350 && e.motion.y < 415){
                cooldown = true;
                break;// TRY AGAIN BUTTON;
            }else if(e.motion.x > 40 && e.motion.x < 130 && e.motion.y > 530 && e.motion.y < 560){
                gameState = false;// EXIT BUTTON
                break;
            }else if(e.motion.x > 10 && e.motion.x < 70 && e.motion.y > 10 && e.motion.y < 70){
                // HOME BUTTON
                MenuState = true;
                play = false;
                break;
            }
        }
        else if(e.type == SDL_QUIT ){
            gameState = false;
            break;
        }
    }
}

