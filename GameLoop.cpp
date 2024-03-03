#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    p.setSource(0, 0, 34, 24);
	p.setDest(50, HEIGHT/2, 55, 35);
    ground1.setSource(0, 0, 112, 336);
	ground1.setDest(0, 520, 112, 805);
	ground2.setSource(0, 0, 112, 336);
	ground2.setDest(805, 520, 112, 805);
	Pipe_Above1.setSource(0, 0, 320, 52);
	Pipe_Above1.setDest(400, -200, 100, 52);
	Pipe_Below1.setSource(0, 0, 320, 52);
	Pipe_Below1.setDest(400, 350, 100, 52);
	Pipe_Above2.setSource(0, 0, 320, 52);
	Pipe_Above2.setDest(700, -200, 100, 52);
	Pipe_Below2.setSource(0, 0, 320, 52);
	Pipe_Below2.setDest(700, 350, 100, 52);
	Pipe_Above3.setSource(0, 0, 320, 52);
	Pipe_Above3.setDest(1000, -200, 100, 52);
	Pipe_Below3.setSource(0, 0, 320, 52);
	Pipe_Below3.setDest(1000, 350, 100, 52);
    Golden_Apple.setSource(0, 0, 300, 300);
    Golden_Apple.setDest(1000, 300, 50, 50);
}

bool GameLoop::getGameState()
{
    return GameState;
}

double last = 0;
void GameLoop::FPSlimit()
{
	double first = SDL_GetTicks();
        if(first - last < FPS)
        {
            SDL_Delay(FPS - (first - last));
        }
    last = first;
}


void GameLoop::Intialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
    TTF_Init();
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OPUS | MIX_INIT_OGG);
	// int result = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
	// cout << result << endl;
    // if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) == -1)
    // {
    //     cout << "Failed to open audio" << endl;
    // }else {cout << " Succeed to open audio " << endl;}
	// //Mix_Music *music = Mix_LoadMUS("Sound/backgroundSound.mp3");
	// //Mix_PlayMusic(music, -1);
	// //MusGame.PlayBgMusic("Sound/backgroundSound.mp3");
    window = SDL_CreateWindow("Flappy MINH", SDL_WINDOWEVENT_ENTER, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if(window)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            cout << "THANH CONG!" <<  endl;
            GameState = true;
            p.CreateTexture("Image/bluebird1.png", renderer);
			p.CreateTexture1("Image/bluebird2.png", renderer);
			p.CreateTexture2("image/bluebird3.png", renderer);
            b1.CreateTexture("Image/background-day.png", renderer);
            b2.CreateTexture("Image/background-night.png", renderer);
			ground1.CreateTexture("Image/base.png", renderer);
			ground2.CreateTexture("Image/base.png", renderer);
			Pipe_Above1.CreateTexture("Image/Pipe_Above.png", renderer);
			Pipe_Below1.CreateTexture("Image/Pipe_Below.png", renderer);
			Pipe_Above2.CreateTexture("Image/Pipe_Above.png", renderer);
			Pipe_Below2.CreateTexture("Image/Pipe_Below.png", renderer);
			Pipe_Above3.CreateTexture("Image/Pipe_Above.png", renderer);
			Pipe_Below3.CreateTexture("Image/Pipe_Below.png", renderer);
            Golden_Apple.CreateTexture("Image/apple.png", renderer);
			score.CreateFont("Font/calibrib.ttf", 38);
			maxScore.CreateFont("Font/calibrib.ttf", 23);
			//MusGame.CreateMusic("Sound/backgroundSound.mp3");
        }
        else
        {
            cout << "NOT CREATED!" << endl;
        }
    }
    else
    {
        cout << "FAILED to create WINDOW" << endl;
    }
}

void GameLoop::Update()
{
	// Feeding NeuralNetwork with real time data
	// neuralNetwork.Update(p.getYpos(), nextCheckPoint);

	// Finding closest Checkpoint !
	// if (Pipe_Below1.getPipe1X() < Pipe_Below2.getPipe2X() && Pipe_Below1.getPipe1X() < Pipe_Below3.getPipe3X())
	// {
	// 	if (Pipe_Below1.getPipe1X() < -5)
	// 	{
	// 		nextCheckPoint = Pipe_Below2.getPipe2Y();
	// 	}
	// 	else
	// 	{
	// 		nextCheckPoint = Pipe_Below1.getPipe1Y();
	// 	}
	// }
	// else if (Pipe_Below2.getPipe2X() < Pipe_Below1.getPipe1X() && Pipe_Below2.getPipe2X() < Pipe_Below3.getPipe3X())
	// {
	// 	if (Pipe_Below2.getPipe2X() < -5)
	// 	{
	// 		nextCheckPoint = Pipe_Below3.getPipe3Y();
	// 	}
	// 	else
	// 	{
	// 		nextCheckPoint = Pipe_Below2.getPipe2Y();
	// 	}
		
	// }
	// else if (Pipe_Below3.getPipe3X() < Pipe_Below1.getPipe1X() && Pipe_Below3.getPipe3X() < Pipe_Below2.getPipe2X())
	// {
	// 	if (Pipe_Below3.getPipe3X() < -5)
	// 	{
	// 		nextCheckPoint = Pipe_Below1.getPipe1Y();
	// 	}
	// 	else
	// 	{
	// 		nextCheckPoint = Pipe_Below3.getPipe3Y();
	// 	}
		
	// }

    // Scoring Mechanics//////
	std::string s;
	s = "Score: " + std::to_string(points);
	score.Text(s, renderer);
	s = "BEST SCORE: " + std::to_string(maxPoints);
	maxScore.Text(s, renderer);
	//////////////////////////
	bool flag1 = false, flag2 = false;
	ground1.GroundUpdate1(speed);
	ground2.GroundUpdate2(speed);
	flag1 = Pipe_Above1.Pipe_Above1Update(variance1, points, speed);
	flag2 = Pipe_Below1.Pipe_Below1Update(variance1, speed);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance1 = rand() % 201 - 100;
		Pipe_Above1.Pipe_Above1Update(variance1, points, speed);
		Pipe_Below1.Pipe_Below1Update(variance1, speed);
	}
	flag1 = Pipe_Above2.Pipe_Above2Update(variance2, points, speed);
	flag2 = Pipe_Below2.Pipe_Below2Update(variance2, speed);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance2 = rand() % 201 - 100;
		Pipe_Above2.Pipe_Above2Update(variance2, points, speed);
		Pipe_Below2.Pipe_Below2Update(variance2, speed);
	}
	flag1 = Pipe_Above3.Pipe_Above3Update(variance3, points, speed);
	flag1 = Pipe_Below3.Pipe_Below3Update(variance3, speed);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance3 = rand() % 201 - 100;
		Pipe_Above3.Pipe_Above3Update(variance3, points, speed);
		Pipe_Below3.Pipe_Below3Update(variance3, speed);
	}
    flag1 = Golden_Apple.Golden_AppleUpdate(variance4, points, speed);
    if(flag1)
    {
        AppleState = true;
        srand(SDL_GetTicks());
        variance4 = rand() % 801 - 300;
        Golden_Apple.Golden_AppleUpdate(variance4, points, speed);
    }
    CollisionDetection();
}

void GameLoop::Event()
{
    p.GetJumpTime();
    SDL_PollEvent(&event1);
    if(event1.type == SDL_QUIT)
    {
        GameState = false;
    }
    if(event1.type == SDL_KEYDOWN)
    {
        if(event1.key.keysym.sym == SDLK_UP || event1.key.keysym.sym == SDLK_w)
        {
            if(!p.JumpState())
            {
                p.Jump();
            }
            else
            {
                p.Gravity();
            }
        }
		else if(event1.key.keysym.sym == SDLK_q) // QUIT the GAME
		{
			GameState = false;
		}
		// else if(event1.key.keysym.sym == SDLK_SPACE)
		// {
		// 	if(Mix_PausedMusic())
		// 	{
		// 		Mix_ResumeMusic();
		// 	}
		// 	else
		// 	{
		// 		Mix_PauseMusic();
		// 	}
		// }
    }
    else
    {
        p.Gravity(); 

    }
}

void GameLoop::CollisionDetection()
{
	if (Collision::CheckCollision(&p.getDest(), &Pipe_Above1.getDest()) || Collision::CheckCollision(&p.getDest(), &Pipe_Below1.getDest()) || 
		Collision::CheckCollision(&p.getDest(), &Pipe_Above2.getDest()) || Collision::CheckCollision(&p.getDest(), &Pipe_Below2.getDest()) || 
		Collision::CheckCollision(&p.getDest(), &Pipe_Above3.getDest()) || Collision::CheckCollision(&p.getDest(), &Pipe_Below3.getDest()))
	{
		SDL_Delay(3000);
		maxPoints = max(points, maxPoints);
		// list.Insert(points, generations);
		// generations++;
		// neuralNetwork.SaveProgress("Progress.txt", generations);
		Reset();
	}
	else if (Collision::CheckCollision(&p.getDest(), &ground1.getDest()) || Collision::CheckCollision(&p.getDest(), &ground2.getDest()) || p.getYpos() < 0)
	{
		SDL_Delay(3000);
		maxPoints = max(points, maxPoints);
		// list.Insert(points, generations);
		// generations++;
		// neuralNetwork.SaveProgress("Progress.txt", generations);
		Reset();
	}
    else if(Collision::CheckCollision(&p.getDest(), &Golden_Apple.getDest()))
    {
        AppleState = false;
    }
}

void GameLoop::Reset()
{
	points = 0;
	FPS = 16.8;
	speed = 2.5;
	variance1 = rand() % 201 - 100;
	variance2 = rand() % 201 - 100;
	variance3 = rand() % 201 - 100;
	p.Reset();
	Pipe_Above1.Reset();
	Pipe_Above2.Reset();
	Pipe_Above3.Reset();
	Pipe_Below1.Reset();
	Pipe_Below2.Reset();
	Pipe_Below3.Reset();
}

void GameLoop::Render()
{
    SDL_RenderClear(renderer);
    if((points / 15) % 2 == 0){
	    b1.Render(renderer);
    }else{
        b2.Render(renderer);
    }
	if(points % 10 == 0 && points >= 10 && speed < 4.5) speed += 0.004; 
	Pipe_Above1.PipeRender(renderer);
	Pipe_Below1.PipeRender(renderer);
	Pipe_Above2.PipeRender(renderer);
	Pipe_Below2.PipeRender(renderer);
	Pipe_Above3.PipeRender(renderer);
	Pipe_Below3.PipeRender(renderer);
    if(AppleState){
        Golden_Apple.GoldenAppleRender(renderer);
    }
	ground1.GroundRender(renderer);
	ground2.GroundRender(renderer);
    score.Render(renderer, 350, 10);
	maxScore.Render(renderer, 7, 7);
	if(!p.JumpState()){
    	p.RenderDown(renderer);
	}else p.RenderUp(renderer);
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
    score.CloseFont();
	TTF_Quit();
	MusGame.CloseMusic();
	Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
