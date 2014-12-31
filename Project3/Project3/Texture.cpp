
#include "Texture.h"
#include <SDL_image.h>
#include <string>
#include <cstdio>

Texture::Texture()
{
	//empty ctor
}

Texture::Texture(std::string path, std::string name,SDL_Renderer* renderer)
{
	load(path,renderer,name);
}

bool Texture::load(std::string path,SDL_Renderer* renderer,std::string texName)
{
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
		SDL_FreeSurface(tempSurface);

	}


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