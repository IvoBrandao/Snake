#include "SnakeFood.h"


SnakeFood::SnakeFood(int foodScale, int mapWidth, int mapHeight)
{
	food_Scale = foodScale;
	map_Width = mapWidth;
	map_Height = mapHeight;
	position_x = 0;
	position_y = 0;
}

SnakeFood::~SnakeFood()
{
}

void SnakeFood::draw(SDL_Renderer* renderer)
{
	SDL_Rect r{ food_Scale * position_x,food_Scale * position_y,food_Scale,food_Scale };


	SDL_SetRenderDrawColor(renderer, 111, 111, 111, 1);

	SDL_RenderFillRect(renderer, &r);

	
}

void SnakeFood::Generate() 
{
	position_x = rand() % (map_Width / food_Scale);

	position_y = rand() % (map_Height / food_Scale);

	checkLimits(position_x, position_y);

}


void SnakeFood::checkLimits(int x, int y)
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