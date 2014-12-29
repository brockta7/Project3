//Game Implementation File

#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

//Game Constructor initializing game and entering game loop/event loop
Game::Game()
{
	//Initialize game subsystems
	initGame();
	//Load Media
	loadMedia();

	//Enter the game loop..
	while(GameIsOver == false)
	{
		//Event Loop
		while(SDL_PollEvent(&eventLoop) != 0)
		{
			if(eventLoop.type == SDL_QUIT)
			{
				GameIsOver = true;
			}
		}

	}

}

//initGame function to initialize all game subsystems
bool Game::initGame()
{
	//Set Screen Values
	SCR_H = 640;
	SCR_W = 480;

	//Success flag to determine if all game subsystems were initialized correctly.
	bool success = true;


	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		success = false;
		printf("SDL has failed to initialize all game subsystems. SDL_Error: %s",SDL_GetError());
	}
	else
	{
		GameWindow = SDL_CreateWindow("Project3",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCR_H,SCR_W,SDL_WINDOW_SHOWN);

		if(GameWindow == NULL)
		{
			success = false;
			printf("Game window has failed to initialize. SDL_Error: %s",SDL_GetError());
		}
		else
		{
			GameRenderer = SDL_CreateRenderer(GameWindow,-1,SDL_RENDERER_ACCELERATED);
			
			if(GameRenderer == NULL)
			{
				success = false;
				printf("Game renderer has failed to initialize. SDL_Error: %s",SDL_GetError());
			}

		}
	}

	GameIsOver = false;
	

	return success;

}


//Load media

void Game::loadMedia()
{
	SDL_Texture* myTexture;

	myTexture = createTexture("bg.png");

}

//Create texures

SDL_Texture* Game::createTexture(string path)
{

	SDL_Texture* aTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	aTexture = SDL_CreateTextureFromSurface(GameRenderer,loadedSurface);
	SDL_FreeSurface(loadedSurface);


	return aTexture;


}