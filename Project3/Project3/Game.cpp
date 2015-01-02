//Game Implementation File

#include "Game.h"
#include "Texture.h"
#include "Sound.h"
#include "Text.h"
#include "Timer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

//Game Constructor initializing game and entering game loop/event loop
Game::Game()
{
	Sound musicLoop;
	Text myText;

	//Timer shit
	std::stringstream timeText;
	Timer fpsTimer;
	Text textForTimer;

	//Initialize game subsystems
	if(initGame() == false)
	{
		printf("Game has failed to initialize. SDL Error: %s",SDL_GetError());
		exit(1);
	}

	//Load Assets
	Texture background("bg.png","Bg",getRenderer());
	musicLoop.loadSFX("mus.wav","");

	//Enter the game loop..
	while(GameIsOver == false)
	{
		//Event Loop
		while(SDL_PollEvent(&eventLoop) != 0)
		{

			if(eventLoop.type == SDL_KEYDOWN)
			{
				if(eventLoop.key.keysym.sym == SDLK_s)
				{
					if(fpsTimer.isStarted())
						fpsTimer.stop();
					else
						fpsTimer.start();
				}
				else if(eventLoop.key.keysym.sym == SDLK_p)
				{
					if(fpsTimer.isPaused())
						fpsTimer.unpause();
					else
						fpsTimer.pause();
				}
				else if(eventLoop.key.keysym.sym == SDLK_0)
					musicLoop.playSFX(1);
			}

			if(eventLoop.type == SDL_QUIT)
			{
				GameIsOver = true;
			}
		}

		//Frames
		timeText.str("");
		timeText << "Timer: " << ( fpsTimer.getTicks() / 1000 );
		std::cout << timeText.str() << std::endl;
		textForTimer.load(timeText.str().c_str(),getRenderer());
		myText.load("Here we gooooooooo!",getRenderer());

		SDL_SetRenderDrawColor(getRenderer(),0xFF,0xFF,0xFF,0xFF);
		SDL_RenderClear(getRenderer());

		background.apply(0,0,getRenderer());
		myText.render(100,100,getRenderer());
		textForTimer.render(100,200,getRenderer());
		SDL_RenderPresent(getRenderer());
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



