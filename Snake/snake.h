#pragma once

#include "SDL.h"
#include "vector"

typedef struct
{
	int x;
	int y;
}BodySegment;

#define TAIL_MAX_LEN (100)


class snake 
{;


private :
	int scale;
	int map_width;
	int map_Height;
	int position_x;
	int position_y;
	int speed_x;
	int speed_y;

	int body_start;
	int body_end;
	int body_len;

	BodySegment body[TAIL_MAX_LEN];


	uint32_t timepassed;

public:
	/*Contructor */
	snake(int snakeScale, int mapWidth, int mapHeight);

	/*Destuctor*/
	~snake();


public:

	void update(int deltaTime);
	void direction(int x, int y);
	void draw(SDL_Renderer* renderer);
	void checkLimits(int x, int y);
	int eat(int FoodPosition_x, int FoodPosition_y);
	void reset(void);
private:

	void constrain(int var, int min, int max,int scale);

};