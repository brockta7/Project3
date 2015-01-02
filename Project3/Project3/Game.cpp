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
	//Game Variables
	Sound musicLoop;
	Text myText;
	Texture background;
	TTF_Font* font;

	//Timer shit
	std::stringstream timeText;
	std::stringstream fpsText;
	Timer regTimer;
	Timer fpsTimer;
	Text textForTimer;
	Text textForFPSTimer;
	int frames = 0; //for fpsTimer
	SDL_Color txtColor = {255,0,0};

	//Initialize game subsystems
	if(initGame() == false)
	{
		printf("Game has failed to initialize. SDL Error: %s",SDL_GetError());
		exit(1);
	}
	//Load Assets
	else
	{
		musicLoop.loadSFX("mus.wav","");
		font = TTF_OpenFont("smb.ttf",48);
		background.load("bg.png",GameRenderer,"Background");
		background.apply(0,0,GameRenderer);

		SDL_RenderPresent(GameRenderer);
		
	}

	//Start Frames Per Second Timer
	fpsTimer.start();
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
					if(regTimer.isStarted())
						regTimer.stop();
					else
						regTimer.start();
				}
				else if(eventLoop.key.keysym.sym == SDLK_p)
				{
					if(regTimer.isPaused())
						regTimer.unpause();
					else
						regTimer.pause();
				}
				else if(eventLoop.key.keysym.sym == SDLK_0)
					musicLoop.playSFX(1);
			}

			if(eventLoop.type == SDL_QUIT)
			{
				GameIsOver = true;
			}
		}


		//Calculate and correct FPS
		float avgFPS = frames / (fpsTimer.getTicks() / 1000.f);

		if(avgFPS > 2000000)
			avgFPS = 0;

		timeText.str("");
		timeText << "Timer: " << ( regTimer.getTicks() / 1000.f );
		fpsText.str("");
		fpsText << "FPS: " << avgFPS;

		
		textForTimer.load(timeText.str().c_str(),GameRenderer,txtColor,font);
		textForFPSTimer.load(fpsText.str().c_str(),GameRenderer,txtColor,font);
		myText.load("Here we gooooooooo!",GameRenderer,txtColor,font);

		SDL_RenderClear(GameRenderer);

		//Render
		background.apply(0,0,GameRenderer);
		myText.render(100,100,GameRenderer);
		textForTimer.render(100,200,GameRenderer);
		textForFPSTimer.render(100,300,GameRenderer);
		SDL_RenderPresent(GameRenderer);
		frames++;
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
				SDL_SetRenderDrawColor(GameRenderer,0xFF,0xFF,0xFF,0xFF);

				if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0 )
				{
					printf("Mixer failed to initialize. SDL_Error: %s",Mix_GetError());
					success = false;
				}

				if(TTF_Init() == -1)
				{
					printf("TTF failed to initialize. SDL_Error: %s",TTF_GetError());
					success = false;
				}
				
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags) )
				{
					printf("SDL_image could not initalize. SDL_Image Error: %s",IMG_GetError());
					success = false;
				}


			}

		}
	}

	GameIsOver = false;
	

	return success;

}



