// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "stdio.h"
#include "cstdlib"
#include "snake.h"
#include "SnakeFood.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int MAP_WIDTH = 800;
const int MAP_HEIGHT = 800;
const int SCALE = 16;


#define SDL_MAIN_HANDLED
#undef main
using namespace std;

int main()
{

	uint32_t Score =0;
	uint32_t current_time = 0;
	uint32_t previous_time = 0;
	uint32_t delta_time = 0;
	SDL_Event event;
	bool running = true;
	snake snek = snake(SCALE, MAP_WIDTH, MAP_HEIGHT);
	
	SnakeFood snakeFood = SnakeFood(SCALE, MAP_WIDTH, MAP_HEIGHT);


	// Setup window for with SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP);

	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAP_WIDTH, MAP_HEIGHT, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// SDL_Surface* image = IMG_Load("/resources/background.JPG");
	// SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	/* Place the food for the snake */
	snakeFood.Generate();


	while (running)
	{
		/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
		/* more events on the event queue, our while loop will exit when */
		/* that occurs.                                                  */
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				running = false;
			}
			break;
			case SDL_KEYDOWN:
			{
				/* Check the SDLKey values and move change the coords */
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
				{
					running = false;
				}
				case SDLK_LEFT:
				{
					snek.direction(-1, 0);
				}
				break;
				case SDLK_RIGHT:
				{

					snek.direction(1, 0);
				}
				break;
				case SDLK_UP:
				{

					snek.direction( 0, -1);
				}
				break;
				case SDLK_DOWN:
				{

					snek.direction(0, 1);
				}
				break;
				default:
					break;
				}
				break;
				/* We must also use the SDL_KEYUP events to zero the x */
				/* and y velocity variables. But we must also be       */
				/* careful not to zero the velocities when we shouldn't*/
				default:
					break;
				}
			}

		}
		

		previous_time = current_time;

		current_time = SDL_GetTicks();

		delta_time = current_time - previous_time;

		snek.update(delta_time);


		int ret_val = snek.eat(snakeFood.position_x, snakeFood.position_y);
		switch (ret_val) 
		{
		case -1:
//			running = false;
			snek.reset();
			break;

		case 0:
			break;

		case 1:
			Score++;
			snakeFood.Generate();
			break;
		}


		// Set the background 
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		/*Clear the map */
		SDL_RenderClear(renderer);

		/* Draw the Snake */
		snek.draw(renderer);

		/* Draw the snake food */
		snakeFood.draw(renderer);

		/* Show the screen */
	//	SDL_Rect dstrect = { 5, 5, 320, 240 };
	//	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	//	SDL_Delay(1);
	} // End Main Game loop

	// SDL_DestroyTexture(texture);
	// SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//IMG_Quit();

	//IMG_Quit();
	return 0;
}


