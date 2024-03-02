#pragma once
#include"include/SDL2/SDL_mixer.h"
#include"include/SDL2/SDL.h"
#include<iostream>

class Sound
{
private:
    Mix_Chunk * sound = NULL;
    Mix_Music *music = NULL;
public:
    bool success = 1;
    void CreateMusic();
    void PlayEffectMusic(const char* fileMP3);
    void PlayBgMusic(const char* fileMP3);
    void CloseMusic();
};