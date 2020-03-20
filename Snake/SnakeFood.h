#pragma once

#include "cstdlib"
#include "SDL.h"


class SnakeFood
{

public:
	int position_x;
	int position_y;
	int food_Scale;
	int map_Width;
	int map_Height;

	/*Contructor */
	SnakeFood(int snakeScale, int mapWidth, int mapHeight);

	/*Destuctor*/
	~SnakeFood();

public:
	void draw(SDL_Renderer* renderer);
	void Generate(void);

private: 
	void checkLimits(int x, int y);
};

