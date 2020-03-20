#include "snake.h"

#define INVALID_COORDINATE -1

snake::snake( int snakeScale, int mapWidth, int mapHeight)
{
	scale = snakeScale;
	map_width = mapWidth;
	map_Height = mapHeight;
	position_x = 0;
	position_y = 0;
	speed_x = 0;
	speed_y = 0;
	body_start = 0;
	body_end = 0;
	body_len = 1;


}

snake::~snake()
{
}

void snake::reset(void) 
{

	position_x = 0;
	position_y = 0;
	speed_x = 0;
	speed_y = 0;
	body_start = 0;
	body_end = 0;
	body_len = 1;

}


void snake::update(int deltaTime)
{
	timepassed += deltaTime;

	if (timepassed > 80)
	{
		timepassed = 0;

		// Update the current position
		position_x = position_x + (speed_x);
		position_y = position_y + (speed_y);

		checkLimits(position_x, position_y);


		for (int i = 0; i < body_len-1; i++)
		{
			body[i].x = body[i+1].x;
			body[i].y = body[i+1].y;
		}
			
		body[body_len-1].x = position_x;
		body[body_len-1].y = position_y;
		
		
	}
}

void snake::direction(int x, int y) 
{
	this->speed_x = x;
	this->speed_y = y;
	
}

void snake::draw(SDL_Renderer* renderer)
{


	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	/* Set the current position of the snake head*/
	SDL_Rect r{ scale * position_x, scale * position_y,scale,scale };

	/* Draw the Head of the Snake */
	SDL_RenderFillRect(renderer, &r);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	
	for (int i = 0; i < body_len; i++) 
	{
		/* Set the current position of the snake head*/
		SDL_Rect r{ scale * body[i].x, scale * body[i].y,scale, scale };

		/* Draw the Head of the Snake */
		SDL_RenderFillRect(renderer, &r);

	}

}

int snake::eat(int FoodPosition_x, int FoodPosition_y)
{
	int return_val = 0;

	bool isDead = false;
	bool isFoodCatched = false;

	for (int i = 0; i < body_len - 1 && !isDead; i++)
	{
		isDead |= ((position_x == body[i].x) && (position_y == body[i].y));
	}

	if ((!isDead) && (position_x == FoodPosition_x) && (position_y == FoodPosition_y)){
		if(body_len < TAIL_MAX_LEN)
		{
			body_len++;
			for (int i = body_len; i > 0; i--)
			{
				body[i].x = body[i - 1].x;
				body[i].y = body[i - 1].y;
			}
			body[0].x = INVALID_COORDINATE;
			body[0].y = INVALID_COORDINATE;

		}

		isFoodCatched = true;
	}
	
	return (isDead ? -1 : isFoodCatched ? 1 : 0);
}

void snake::checkLimits(int x, int y) 
{
		if (x < 0)
		{
			position_x = 49;
		}

		if (y < 0)
		{
			position_y = 49;
		}

		if (x >= 50)
		{
			position_x = 0;
		}

		if (y >= 50)
		{
			position_y = 0;
		}
}

void snake::constrain(int var, int min, int max, int scale) 
{

	if (var < min) 
	{
		var = min;
	}

	if (var > max) 
	{
		var = max/ scale;
	}
}