
#include "Texture.h"
#include <SDL_image.h>
#include <string>
#include <cstdio>

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
	name = "";
}

Texture::~Texture()
{
	freeUp();
}


bool Texture::load(std::string path,SDL_Renderer* renderer,std::string texName)
{
	freeUp();

	bool success = true;
	name = texName;

	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(path.c_str());

	if(tempSurface == NULL)
	{
		printf("Load function failed to load tempSurface. SDL_Error: %s",SDL_GetError());
		success = false;
	}
	else
	{
		width = tempSurface->w;
		height = tempSurface->h;
		texture = SDL_CreateTextureFromSurface(renderer,tempSurface);
	}

	SDL_FreeSurface(tempSurface);

	return success;

}

bool Texture::apply(int x, int y,SDL_Renderer* renderer)
{
	bool success = true;

	SDL_Rect dimensions = {x,y,width,height};

	if(SDL_RenderCopyEx(renderer,texture,NULL,&dimensions,NULL,NULL,SDL_FLIP_NONE) == -1)
	{
		printf("Failed to render. SDL_Error: %s .",SDL_GetError());
	}


	return success;
}

void Texture::freeUp()
{
	if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}



}