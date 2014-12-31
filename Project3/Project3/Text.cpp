
#include "Text.h"
#include <cstdio>

Text::Text()
{
	renderedText = NULL;
}


void Text::load(std::string message,SDL_Renderer* renderer)
{
	SDL_Color txtColor = {255,0,0};
	TTF_Font* font = TTF_OpenFont("night.ttf",48);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font,message.c_str(),txtColor);
	if(textSurface == NULL)
	{
		printf("Failed to load text to textSurface. SDL_Error: %s",TTF_GetError());
	}
	else
	{
		renderedText = SDL_CreateTextureFromSurface(renderer,textSurface);

		if(renderedText == NULL)
			printf("Failed to load text to renderedText texture. SDL_Error: %s",SDL_GetError());
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
}

void Text::render(int x, int y, SDL_Renderer* renderer)
{

	SDL_Rect dimensions = {x,y,width,height};

	if(SDL_RenderCopyEx(renderer,renderedText,NULL,&dimensions,NULL,NULL,SDL_FLIP_NONE) == -1)
	{
		printf("Failed to render text. SDL_Error: %s .",SDL_GetError());
	}

}