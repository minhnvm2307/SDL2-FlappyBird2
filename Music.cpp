#include"Music.h"
using namespace std;
void Sound::CreateMusic()
{
    // LOADING BACKGROUND MUSIC/////////////////////////////
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OPUS | MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    // if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) == -1)
    // {
    //     cout << "Failed to open audio" << endl;
    // }else {cout << " Succeed to open audio " << endl;}
    ////////////////////////////////////////////////////////
}

void Sound::PlayBgMusic(const char* fileMP3)
{
    music = Mix_LoadMUS(fileMP3);
    if(music == NULL)
    {
        cout << "Fail to load MUS  " << Mix_GetError() << endl;
    }else cout << "succeed to load MUS" << endl;

    //Mix_PlayMusic(music, -1);
    if(Mix_PlayMusic(music, -1) == -1)
    {
        cout << "Failed to play Music !  " << Mix_GetError() << endl;
    }else cout << "succeed to play" << endl;
}

// void Sound::PlayEffectMusic(const char* fileMP3)
// {
//     Mix_Chunk * music = 
// }

void Sound::CloseMusic()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;
    Mix_CloseAudio();
}