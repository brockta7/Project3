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
	//Free Memory
	void close();
	//Load the media
	SDL_Renderer* getRenderer() { return GameRenderer; }

private:
	//Screen Dimensions
	int SCR_H;
	int SCR_W;
	//Quit flag
	bool GameIsOver;
	//Main event loop
	SDL_Event eventLoop;
	//Game Window
	SDL_Window* GameWindow;
	//Game Renderer
	SDL_Renderer* GameRenderer;


};

#endif