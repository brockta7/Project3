#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>

using std::string;

class Game
{
public:
	//Constructor
	Game();
	//Initialize the subsystems
	bool initGame();
	//Load the media
	void loadMedia();
	//Load/Create a Texture
	SDL_Texture* createTexture(string path);
	//Apply a Texture to Game world.
	void applyTexture();

protected:
	//Screen Dimensions
	int SCR_H;
	int SCR_W;
	//Game Window
	SDL_Window* GameWindow;
	//Game Renderer
	SDL_Renderer* GameRenderer;
	//Quit flag
	bool GameIsOver;
	//Main event loop
	SDL_Event eventLoop;


};

#endif