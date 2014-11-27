#include <string>
#include <vector>
#include <limits>
#include <time.h>
#include <iostream>
#include "AIE.h"

using namespace std;

typedef vector<vector<bool>> Grid;

const int width = 600;
const int height = 600;

const float chanceToStartAlive =45.0f;

/*
rules:
If a living cell has less than two living neighbours, it dies.
If a living cell has two or three living neighbours, it stays alive.
If a living cell has more than three living neighbours, it dies.
If a dead cell has exactly three living neighbours, it becomes alive.
*/

void InitMap(Grid& a_grid)
{
	for (int x = 0; x < width; x+=10)
	{
		for (int y = 0; y < height; y+=10)
		{
			if ((rand() % 100) < chanceToStartAlive)
			{
				a_grid[x][y] = true;
			}
		}
	}
}

/*
return number of neighbor to the given position in given grid are alive
*/
int CountAliveNeighbors(const Grid& a_map, const int x, const int y)
{
	int result = 0;
	for (int i = -10; i < 20; i+=10)
	{
		for (int j = -10; j < 20; j+=10)
		{
			int neighborX = x + i;
			int neighborY = y + j;

			//if looking in middle point
			if (i == 0 && j == 0)
			{
				//do nothing, don't want to add 
			}
			//in case the index we'relooking at it off the edge of the grid
			else if (neighborX < 0 || neighborY < 0 || neighborX >= a_map.size() || neighborY >= a_map[0].size())
			{
				//count it
				result++;
			}
			//otherwise, check normal
			else if (a_map[neighborX][neighborY])
			{
				result++;
			}
		}
	}
	return result;
}

/*
rules:
If a living cell has less than two living neighbours, it dies.
If a living cell has two or three living neighbours, it stays alive.
If a living cell has more than three living neighbours, it dies.
If a dead cell has exactly three living neighbours, it becomes alive.
*/

const int deathLimit = 3;
const int birthLimit = 4;

/*
Perform one round of life simulation using rules. This function will modify given grid
*/
void DoSimStep(Grid& a_map)
{
	Grid newMap(width, vector<bool>(height, false));
	for (int x = 0; x < a_map.size(); x+=10)
	{
		for (int y = 0; y < a_map[0].size(); y+=10)
		{
			int neighborCount = CountAliveNeighbors(a_map, x, y);
			//the new value based on rules
			if (a_map[x][y])
			{
				//if cell is alive, but has too few neighbors kill it
				if (neighborCount < deathLimit)
				{
					newMap[x][y] = false;
				}
				//////if cell is alive and has too many neigbors kill it
				//else if (neighborCount > birthLimit)
				//{
				//	newMap[x][y] = false;
				//}
				//if cell is alive and has enough neighbors it stays alive
				else
				{
					newMap[x][y] = true;
				}
			}
			//if cell is dead and has 3 neighbors 
			else if (neighborCount > birthLimit)
			{
				newMap[x][y] = true;
			}
			else
			{
				newMap[x][y] = false;
			}
		}
	}

	a_map = newMap;
}

void Update(Grid& map, const unsigned int sprite)
{
	for (int x = 0; x < width; x += 10)
	{
		for (int y = 0; y < height; y += 10)
		{
			if (map[x][y])
				MoveSprite(sprite, x, y);
		}
	}
}

void main(){
	//TestCount();


	Initialise(width, height, false, "Test Game");
	SetBackgroundColour(SColour(255, 255, 255, 255));
	bool quit = false;
	int count = 0;

	//set seed
	srand(time(nullptr));
	//initalize 2d vector to false
	Grid cellMap(width, vector<bool>(height, false));
	InitMap(cellMap);

	/*for (int i = 0; i < 5; i++)
		DoSimStep(cellMap);*/

	unsigned int pixel = CreateSprite("images/pixel_10.png", 10, 10, true);
	//Update(cellMap, pixel);
	//MoveSprite(pixel, width * .25, height - 100);
	do
	{
		SetFont("./fonts/invaders.fnt");
		for (int x = 0; x < width; x+=10)
		{
			for (int y = 0; y < height; y+=10)
			{
				if (cellMap[x][y])
				{
					MoveSprite(pixel, x, y);
					DrawSprite(pixel);
				}

			}
		}
		if (IsKeyDown(KEY_SPACE))
		{
			DoSimStep(cellMap);
		}
		if (IsKeyDown('Q'))
		{
			quit = true;
		}
		ClearScreen();
	} while (!FrameworkUpdate() && !quit);



	Shutdown();
	//system("pause");
}

