#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

class Texture 
{
public:
	Texture();
	~Texture();
	bool load(std::string path,SDL_Renderer* renderer, std::string texName);
	bool apply(int x, int y,SDL_Renderer* renderer);
	void freeUp(); // free up previously used texture
private:
	std::string name;
	int width;
	int height;
	SDL_Texture* texture;
};

#endif