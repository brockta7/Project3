//Game Implementation File

#include "Game.h"
#include "Texture.h"
#include "Sound.h"
#include "Text.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

//Game Constructor initializing game and entering game loop/event loop
Game::Game()
{
	Sound musicLoop;
	Text myText;

	//Initialize game subsystems
	if(initGame() == false)
	{
		printf("Game has failed to initialize. SDL Error: %s",SDL_GetError());
		exit(1);
	}
	//Load Assets
	else
	{
		Texture background("bg.png","Bg",getRenderer());
		background.apply(0,0,getRenderer());
		musicLoop.loadSFX("mus.wav","");
		myText.load("Ass and titties all day.",getRenderer());
		myText.render(100,100,getRenderer());
		SDL_RenderPresent(getRenderer());
		
	}


	//Enter the game loop..
	while(GameIsOver == false)
	{
		//Event Loop
		while(SDL_PollEvent(&eventLoop) != 0)
		{

			switch(eventLoop.key.keysym.sym)
			{
			case SDLK_0:
				musicLoop.playSFX(1);
				break;

			}

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
	SCR_H = 1280;
	SCR_W = 960;

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
			else
			{
				if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0 )
				{
					printf("Mixer failed to initialize. SDL_Error: %s",Mix_GetError());
					success = false;
				}
				else
				{

					if(TTF_Init() == -1)
					{
						printf("TTF failed to initialize. SDL_Error: %s",TTF_GetError());
					}
				}
				

			}

		}
	}

	GameIsOver = false;
	

	return success;

}



