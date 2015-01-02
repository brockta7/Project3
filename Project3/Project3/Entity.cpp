#include "Entity.h"


Entity::Entity()
{
	xPos = 0;
	yPos = 880;

	xVel = 0;
	yVel = 0;

}

void Entity::load(std::string path,SDL_Renderer* renderer, std::string name)
{
	entityTexture.load(path,renderer,name);
}

void Entity::handleEvent(SDL_Event& e)
{
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{

		switch(e.key.keysym.sym)
		{
			case SDLK_UP:
				yVel -= velocity;
				break;
			case SDLK_DOWN:
				yVel += velocity;
				break;
			case SDLK_LEFT:
				xVel -= velocity;
				break;
			case SDLK_RIGHT:
				xVel += velocity;
				break;
		}
	}

	if(e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_UP:
				yVel += velocity;
				break;
			case SDLK_DOWN:
				yVel -= velocity;
				break;
			case SDLK_LEFT:
				xVel += velocity;
				break;
			case SDLK_RIGHT:
				xVel -= velocity;
				break;
		}
	}

}

void Entity::move()
{

	xPos += xVel;

	if( (xPos < 0 ) || (xPos + width > 1280))
		xPos -= xVel;

	yPos += yVel;


	if( (yPos < 0) || (yPos + height > 960))
		yPos -= yVel;

}


void Entity::render(SDL_Renderer* renderer)
{
	entityTexture.apply(xPos,yPos,renderer);
}


