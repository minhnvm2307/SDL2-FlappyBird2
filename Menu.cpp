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
    settingItem.GroundRender(ren);
    if(settingState) {
        settingMenu.GroundRender(ren);
        DifficultyState.Render(ren, 420, 283);
        Bmusic.Render(ren, 420, 337);
    }
    if(tutorState)
    {
        tutorial.GroundRender(ren);
    }
}

void menu::MakeChoosingBird(SDL_Renderer* ren)
{
    leaderB.CreateTexture("Image/leaderboard.png", ren);
    leaderB.setSource(0, 0, 460, 598);
    leaderB.setDest(0, 0, 460, 598);

    vItem.CreateTexture("Image/vItem.png", ren);
    vItem.setSource(0, 0, 360, 360);
    vItem.setDest(290, 320, 55, 55);

    choosingBird.CreateTexture("Image/choosingBird.png", ren);
    choosingBird.setSource(0, 0, 500, 300);
    choosingBird.setDest(150, 250, 500, 300);

    tutorial.CreateTexture("Image/Tutorial.png", ren);
    tutorial.setSource(0, 0, 611, 450);
    tutorial.setDest(110, 90, 611, 450);
}

void menu::makeSetting(SDL_Renderer *ren)
{
    DifficultyState.CreateFont("Font/calibrib.ttf", 30);
    DifficultyState.Text(Diff2, ren, blue);

    Bmusic.CreateFont("Font/calibrib.ttf", 28);
    if(musicState) Bmusic.Text(On, ren, blue);

    point.CreateFont("Font/Micro5.ttf", 100);
    maxPoint.CreateFont("Font/Micro5.ttf", 100);
    newRecord.CreateFont("Font/calibrib.ttf", 30);
    newRecord.Text("NEW!!", ren, red);
    newRecord.setDst(410, 310);
    
    settingItem.CreateTexture("Image/setting.png", ren);
    settingItem.setSource(0, 0, 24, 24);
    settingItem.setDest(720, 10, 60, 60);
    settingMenu.CreateTexture("Image/difficultyMenu.png", ren);
    settingMenu.setSource(0, 0, 510, 290);
    settingMenu.setDest(140, 190, 510, 290);

    endGame.CreateTexture("Image/endGame.png", ren);
    endGame.setSource(0, 0, 404, 278);
    endGame.setDest(200, 170, 404, 278);
}

void menu::RenderChoosingBird(SDL_Renderer *ren)
{
    choosingBird.GroundRender(ren);
    vItem.GroundRender(ren);
}

void menu::eventMouse(SDL_Event& ev, Player &p, bool &GameState, bool &MenuState, bool &BirdState, bool &hard, SDL_Renderer* renderer)
{
    SDL_PollEvent(&ev);
    if(BirdState && count < 100) count++;// waiting for birdmenu showned to continue
    if(ev.type == SDL_QUIT || (ev.type == SDL_MOUSEBUTTONDOWN && ev.motion.x > 300 && ev.motion.x < 510 && ev.motion.y > 400 && ev.motion.y < 435 && settingState==1))
    {
        MenuState = false;
        GameState = false;
        play = true;
    }
    else if(ev.type == SDL_MOUSEBUTTONDOWN)
    {
        if(ev.motion.x > 350 && ev.motion.x < 453 && ev.motion.y > 368 && ev.motion.y < 425 && BirdState==false && settingState==false && tutorState==false)//  PLAY BUTTON 
        {   
            MenuState = false;
            play = true;

        }
        else if(ev.motion.x > 350 && ev.motion.x < 453 && ev.motion.y > 440 && ev.motion.y < 475 && BirdState==false && settingState==false && tutorState==false)//OPEN MENU BIRD
        { 
            BirdState = true;
        }
        else if(ev.motion.x > 150 && ev.motion.x < 190 && ev.motion.y > 260 && ev.motion.y < 290)//CLOSE MENU BIRD
        {   count = 0;
            BirdState = false;
        }
        else if(ev.motion.x > 350 && ev.motion.x < 453 && ev.motion.y > 480 && ev.motion.y < 515 && BirdState==false && settingState==false && BirdState==false)
        {
            tutorState = true;
        }
        else if(ev.motion.x > 100 && ev.motion.x < 170 && ev.motion.y > 90 && ev.motion.y < 150)
        {
            tutorState = false;
        }
        else if(ev.motion.x > 730 && ev.motion.y < 80 && BirdState==false && tutorState==false)// Open SETTING
        {
            if(settingState==0){
                settingState=1;
            }else settingState = 0;
        }
        else if(ev.motion.x > 530 && ev.motion.x < 560 && ev.motion.y > 280 && ev.motion.y < 310 && settingState==1){// Change Difficulty
                if(hard==1){
                    hard = 0; ptrHard = 0;
                    DifficultyState.Text(Diff1, renderer, red);// DIFFICULT
                }else{
                    hard = 1; ptrHard = 1;
                    DifficultyState.Text(Diff2, renderer, blue);// EASY
                }
                std::cout << "HARD = " << hard << std::endl;
        }
        else if(ev.motion.x > 500 && ev.motion.x < 530 && ev.motion.y > 330 && ev.motion.y < 360 && settingState==1)// TURN ON/OFF background MUSIC
        {
            if(Mix_PausedMusic())
			{
                musicState = 1;
                Bmusic.Text(On, renderer, blue);
				Mix_ResumeMusic();
			}else{
                musicState = 0;
                Bmusic.Text(Off, renderer, red);
				Mix_PauseMusic();
			}
        }
        if(BirdState == true && count == 100) 
        {
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

void menu::gameContinue(SDL_Renderer *ren, SDL_Event& e, bool &gameState, bool &MenuState, bool &cooldown, int score, int maxScore)
{
    point.Text(std::to_string(score), ren, white);
    maxPoint.Text(std::to_string(maxScore), ren, white);
    upDateBoard(score, ren);
    while(1)
    {
		endGame.GroundRender(ren);
        point.Render(ren, 280, 240);
        maxPoint.Render(ren, 280, 340);
        
        if(maxScore > prevMaxPoint){
            newRecord.RenderAngle(ren, 30);
        }
        if(leaderState) leaderBoard(ren);
		SDL_RenderPresent(ren);

        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(e.motion.x > 500 && e.motion.x < 580 && e.motion.y > 320 && e.motion.y < 400){
                cooldown = true;
                if(musicState)
                {
                    Mix_ResumeMusic();
                }
                break;// TRY AGAIN BUTTON;
            }else if(e.motion.x > 500 && e.motion.x < 580 && e.motion.y > 210 && e.motion.y < 290){
                // HOME BUTTON
                if(musicState)
                {
                    Mix_ResumeMusic();
                }
                MenuState = true;
                play = false;
                break;
            }else if(e.motion.x > 420 && e.motion.x < 490 && e.motion.y > 350 && e.motion.y < 420){
                leaderState = (leaderState==1)? 0:1;
            }
        }
        else if(e.type == SDL_QUIT ){
            gameState = false;
            break;
        }
    }
    prevMaxPoint = maxScore;
}

void menu::leaderBoard(SDL_Renderer* ren)
{
    leaderB.GroundRender(ren);
    for(int i=0; i<saveRen.size(); i++){
        saveRen[i].Render(ren, 100, 180 + 40*(i));
    }
}

void menu::upDateBoard(int score, SDL_Renderer* ren)
{
    saveScore.clear();
    ifstream inFile("saveScore.txt");
    string h = to_string(score);
    saveScore.push_back(h);
    while(inFile >> h){
        saveScore.push_back(h);
    }
    inFile.close();
    ///
    saveMode.clear();
    ifstream inFile2("saveMode.txt");
    h = (ptrHard==1)? "Easy" : "Difficult";
    saveMode.push_back(h);
    while(inFile2 >> h){
        saveMode.push_back(h);
    }
    inFile2.close();
    ////////////////////
    ofstream outFile("saveScore.txt");
    for(int i=0; i<saveScore.size(); i++){
        outFile << saveScore[i] << " ";
    }
    outFile.close();
    ///
    ofstream outFile2("saveMode.txt");
    for(int i=0; i<saveMode.size(); i++){
        outFile2 << saveMode[i] << " ";
    }
    outFile2.close();
    ////////////////////
    TextShow tmp;
    tmp.CreateFont("Font/calibrib.ttf", 40);
    if(saveRen.empty()){
        for(int i=0; i<saveScore.size(); i++){
            h = saveScore[i] + "             " + saveMode[i];
            tmp.Text(h, ren, white);
            saveRen.push_back(tmp);
        }
    }else{
        h = saveScore.front() + "             " + saveMode.front();
        tmp.Text(h, ren, white);
        saveRen.push_back(tmp);
    }
    tmp.CloseFont();
}

void menu::closeLeaderBoard()
{
    saveScore.clear();
    saveMode.clear();
    for(int i=0; i<saveRen.size(); i++){
        saveRen[i].CloseFont();
    }
}

