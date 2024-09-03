#include "audio.h"

void initAudio(void)
{
	memset(sound,0,sizeof(Mix_Chunk));

	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024) == -1)
        {
                printf("Mix_OpenAudio error: %s\n", SDL_GetError());
        }
        else
        {
                Mix_AllocateChannels(MAX_SND_CHANNELS);
        }

	loadSound();
}

static void loadSound(void)
{
	sound[0] = Mix_LoadWAV("assets/sounds/");
	sound[1] = Mix_LoadWAV("assets/sounds/");
	sound[2] = Mix_LoadWAV("assets/sounds/shell_default.ogg");
	sound[3] = Mix_LoadWAV("assets/sounds/");
	sound[4] = Mix_LoadWAV("assets/sounds/hit_wall_def01.ogg");
}

void playSound(unsigned short int id)
{
	if(!Mix_Playing(2) && !id)Mix_PlayChannel(1, sound[id],0);
	if(!Mix_Playing(4) && id == 2)Mix_PlayChannel(2, sound[id],0);
	else if(id && id != 1) Mix_PlayChannel(-1, sound[id],0);
}

void playMusic()
{
        srand(time(NULL));
        int track = rand() % 17 + 1;
        char filename[256];
        snprintf(filename, sizeof(filename), "assets/music/track%d.ogg", track);
        Mix_Music *music = Mix_LoadMUS(filename);
        if(!music)
        {
                printf("Mix_LoadMUS error: %s\n", Mix_GetError());
                return;
        }
        Mix_PlayMusic(music, -1);
}
