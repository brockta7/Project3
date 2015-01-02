#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "Texture.h"
#include <string>

class Entity {

public:
	static const int width = 20;
	static const int height = 20;
	static const int velocity = 2;

	Entity();
	void load(std::string path,SDL_Renderer* renderer, std::string name);
	void handleEvent(SDL_Event& e);
	void move();
	void render(SDL_Renderer* renderer);

private:
	Texture entityTexture;
	int xPos, yPos;
	int xVel, yVel;
};


#endif