#include "Sound.h"
#include <string>

Sound::Sound()
{
	music = NULL;
	sfx1 = NULL;
	sfx2 = NULL;
}


void Sound::loadSFX(std::string path1, std::string path2)
{
	sfx1 = Mix_LoadWAV(path1.c_str());

	if(!path2.empty())
	{
		sfx2 = Mix_LoadWAV(path2.c_str());
	}

	music = NULL;

}


void Sound::loadMUS(std::string path)
{
	music = Mix_LoadMUS(path.c_str());

	sfx1 = NULL;
	sfx2 = NULL;
}

void Sound::playSFX(int fx)
{

	if(fx == 1)
		Mix_PlayChannel(-1,sfx1,0);
	else
		Mix_PlayChannel(-1,sfx2,0);
}

void Sound::playMUS()
{
	Mix_PlayMusic(music,-1);
}




