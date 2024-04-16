#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    p.setSource(0, 0, 34, 24);
	p.setDest(50, HEIGHT/2, 55, 34);
	armor.setSource(0, 0, 56, 50);
	armor.setDest(50, HEIGHT/2, 60, 60);
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
	cnt1.setSource(0, 0, 24, 36);
    cnt1.setDest(378, 210, 50, 80);
	cnt2.setSource(0, 0, 24, 36);
    cnt2.setDest(378, 210, 50, 80);
	cnt3.setSource(0, 0, 24, 36);
    cnt3.setDest(378, 210, 50, 80);
	ready.setSource(0, 0, 183, 171);
	ready.setDest(270, 300, 260, 160);
}

bool GameLoop::getGameState()
{
    return GameState;
}

bool GameLoop::getMenuState()
{
	return MenuState;
}

void GameLoop::Intialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
    TTF_Init();
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OPUS | MIX_INIT_OGG);
	// PLAYING MUSIC//////////////////////////
    if(Mix_OpenAudioDevice(48000,AUDIO_F32SYS , 2, 2048, NULL, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE))
    {
        cout << "Failed to open audio" << Mix_GetError() << endl;
    }else cout << " Succeed to open audio " << endl;
	music = Mix_LoadMUS("Sound/backgroundSound2.mp3");
	if(music == NULL)
	{
		cout << "Failed to load MUS " << Mix_GetError() << endl;
	}else {
		cout << "loaded mus" << endl;
		Mix_PlayMusic(music, -1);
	}
	Jumpsound = Mix_LoadWAV("Sound/sfx_wing.wav");
	Hitsound = Mix_LoadWAV("Sound/sfx_hit.wav");
	Getsound = Mix_LoadWAV("Sound/sfx_point.wav");
	////////PLAYING MUSIC/////////////////////
    window = SDL_CreateWindow("NguyenVanMinh-23020117", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if(window)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            cout << "THANH CONG!" <<  endl;
			GameState = true;
			p.CreateTexture("Image/bird1.png", renderer);
		    p.CreateTexture1("Image/bird2.png", renderer);
		    p.CreateTexture2("Image/bird3.png", renderer);
			armor.CreateTexture("Image/shield.png", renderer);
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
			cnt3.CreateTexture("Image/3.png", renderer);
			cnt2.CreateTexture("Image/2.png", renderer);
			cnt1.CreateTexture("Image/1.png", renderer);
			ready.CreateTexture("Image/ready.png", renderer);
			score.CreateFont("Font/Micro5.ttf", 120);
			maxScore.CreateFont("Font/Micro5.ttf", 40);
			Main.MakeChoosingBird(renderer);
			Main.makeMenu(renderer);
			Main.makeSetting(renderer);
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

void GameLoop::countDown()
{
	cnt3.GroundRender(renderer);
	ready.GroundRender(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	cnt2.GroundRender(renderer);
	ready.GroundRender(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	cnt1.GroundRender(renderer);
	ready.GroundRender(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
}

void GameLoop::menu()
{
	while(!Main.getPlayState())
	{
		Main.eventMouse(event1, p, GameState, MenuState, BirdState, hard, renderer);
		SDL_RenderClear(renderer);
		Main.Render(renderer);
		if(BirdState) Main.RenderChoosingBird(renderer);
		SDL_RenderPresent(renderer);
	}
	if(GameState) cooldownState = true;
}

void GameLoop::Update()
{
    // Scoring Mechanics//////
	std::string s;
	s = std::to_string(points);
	score.Text(s, renderer, white);
	s = "BEST SCORE: " + std::to_string(maxPoints);
	maxScore.Text(s, renderer, white);
	//////////////////////////
	bool flag1 = false, flag2 = false;
	ground1.GroundUpdate1(speed);
	ground2.GroundUpdate2(speed);
	flag1 = Pipe_Above1.Pipe_Above1Update(variance1, var1, points, speed, hard);
	flag2 = Pipe_Below1.Pipe_Below1Update(variance1, var1, speed, hard);
	if (flag1 && flag2)
	{
		if(shield>0) shield--;
		Mix_PlayChannel(5, Getsound, 0);
		srand(SDL_GetTicks());
		variance1 = rand() % 201 - 100;
		var1 = rand() % 60 + 30; 
		Pipe_Above1.Pipe_Above1Update(variance1, var1, points, speed, hard);
		Pipe_Below1.Pipe_Below1Update(variance1, var1, speed, hard);
	}
	flag1 = Pipe_Above2.Pipe_Above2Update(variance2, var2, points, speed, hard);
	flag2 = Pipe_Below2.Pipe_Below2Update(variance2, var2, speed, hard);
	if (flag1 && flag2)
	{
		if(shield>0) shield--;
		Mix_PlayChannel(5, Getsound, 0);
		srand(SDL_GetTicks());
		variance2 = rand() % 201 - 100;
		var2 = rand() % 60 + 30;
		Pipe_Above2.Pipe_Above2Update(variance2, var2, points, speed, hard);
		Pipe_Below2.Pipe_Below2Update(variance2, var2, speed, hard);
	}
	flag1 = Pipe_Above3.Pipe_Above3Update(variance3, var3, points, speed, hard);
	flag1 = Pipe_Below3.Pipe_Below3Update(variance3, var3, speed, hard);
	if (flag1 && flag2)
	{
		if(shield) shield--;
		Mix_PlayChannel(5, Getsound, 0);
		srand(SDL_GetTicks());
		variance3 = rand() % 201 - 100;
		var3 = rand() % 60 + 30;
		Pipe_Above3.Pipe_Above3Update(variance3, var3, points, speed, hard);
		Pipe_Below3.Pipe_Below3Update(variance3, var3, speed, hard);
	}
    flag1 = Golden_Apple.Golden_AppleUpdate(variance4, speed);
    if(flag1)
    {
		Mix_PlayChannel(5, Getsound, 0);
        AppleState = true;
        srand(SDL_GetTicks());
        variance4 = rand() % 751 - 250;
        Golden_Apple.Golden_AppleUpdate(variance4, speed);
    }
    CollisionDetection();
}

void GameLoop::Event()
{
    SDL_PollEvent(&event1);
    if(event1.type == SDL_QUIT)
    {
        GameState = false;
    }
	if(event1.type == SDL_MOUSEBUTTONDOWN || event1.type == SDL_KEYDOWN)
	{
		if((event1.motion.x < WIDTH && event1.motion.x > 0 && event1.motion.y > 0 && event1.motion.y < HEIGHT) || event1.key.keysym.sym == SDLK_UP){
			if(!p.JumpState() && !pDeath)
            {
                p.Jump();
				armor.Jump();
				Mix_PlayChannel(1, Jumpsound, 0);
            }
            else
            {
                p.Gravity();
				armor.ArmorGravity();
            }
		}
	}
    else
    {
        p.Gravity(); 
		armor.ArmorGravity();

    }
}

void GameLoop::CollisionDetection()
{
	if (Collision::CheckCollision(&p.getDest(), &Pipe_Above1.getDest(), shield) || Collision::CheckCollision(&p.getDest(), &Pipe_Below1.getDest(), shield) || Collision::CheckCollision(&p.getDest(), &Pipe_Above2.getDest(), shield) || Collision::CheckCollision(&p.getDest(), &Pipe_Below2.getDest(), shield) || Collision::CheckCollision(&p.getDest(), &Pipe_Above3.getDest(), shield) || Collision::CheckCollision(&p.getDest(), &Pipe_Below3.getDest(), shield))
	{
		Mix_PlayChannel(2, Hitsound, 0);
		speed = 0;
		pDeath = true;
	}
	if(p.getYpos() >= 490)
	{
		Mix_PlayChannel(2, Hitsound, 0);
		Mix_PauseMusic();
		maxPoints = max(points, maxPoints);
		std::string s = "BEST SCORE: " + std::to_string(maxPoints);
		maxScore.Text(s, renderer, white);
		SDL_Delay(1500);
		Main.gameContinue(renderer, event1, GameState, MenuState, cooldownState, points, maxPoints);
		Reset();
	}
    else if(Collision::CheckAppleCollision(&p.getDest(), &Golden_Apple.getDest()) && !pDeath)
    {
        AppleState = false;
		shield = 4; // invisible through 5 pipes
    }
}

void GameLoop::Reset()
{
	points = 0;
	shield = 0;
	speed = 2.8;
	pDeath = 0;
	variance1 = rand() % 201 - 100;
	variance2 = rand() % 201 - 100;
	variance3 = rand() % 201 - 100;
	variance4 = rand() % 751 - 250;
	var1 = rand() % 60 + 30;
	var2 = rand() % 60 + 30;
	var3 = rand() % 60 + 30;
	p.Reset(); armor.Reset();
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
	if(cooldownState) Reset();
    if((points / 15) % 2 == 0){
	    b1.Render(renderer);
    }else{
        b2.Render(renderer);
    }
	speed += 0.0005f;
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
    score.Render(renderer, 390, 10);
	maxScore.Render(renderer, 7, 7);
	p.Render(renderer);
    if(shield) armor.RenderShield(renderer);
	if(!MenuState && GameState && cooldownState) {
		countDown();
		cooldownState = false;
	}
	SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
    score.CloseFont();
	Mix_HaltMusic();
	Mix_FreeMusic(music); music = NULL;
	Mix_FreeChunk(Jumpsound); Jumpsound = NULL;
	Mix_FreeChunk(Hitsound); Hitsound = NULL;
	Mix_FreeChunk(Getsound); Getsound = NULL;
	TTF_Quit();
	Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
