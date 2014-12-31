#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <string>

class Sound
{
public:
	Sound();
	Sound(std::string musicPath); // 1 Music Loop
	Sound(std::string sfx1Path, std::string sfx2Path); // 1 Sound Effect

	void loadSFX(std::string path1, std::string path2);
	void loadMUS(std::string path);
	void playSFX(int fx);
	void playMUS();

private:
	Mix_Music *music;
	Mix_Chunk *sfx1;
	Mix_Chunk *sfx2;

};

#endif