#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include <string>

class Text
{
public:

	Text();
	~Text();
	void setFont(std::string path,int ptSize,SDL_Color color);
	void load(std::string message, SDL_Renderer* renderer,SDL_Color txtColor,TTF_Font* font);
	void render(int x, int y, SDL_Renderer* renderer);
	void freeUp(); // free memory
private:
	SDL_Texture* renderedText;
	int width;
	int height;
};


#endif