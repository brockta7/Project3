#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

class Texture 
{
public:
	Texture();
	Texture(std::string path, std::string name,SDL_Renderer* renderer);
	bool load(std::string path,SDL_Renderer* renderer, std::string texName);
	bool apply(int x, int y,SDL_Renderer* renderer);
private:
	std::string name;
	int width;
	int height;
	SDL_Texture* texture;
};

#endif