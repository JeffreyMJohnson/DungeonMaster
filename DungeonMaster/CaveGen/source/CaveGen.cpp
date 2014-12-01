#include <string>
#include <vector>
#include <limits>
#include <time.h>
#include <iostream>
#include "AIE.h"
#include "EasyBMP.h"
#include "TheMath.h"

using namespace std;

typedef vector<vector<bool>> Grid;

const int width = 600;
const int height = 600;

const float chanceToStartAlive = 45.0f;

/*
rules:
If a living cell has less than two living neighbours, it dies.
If a living cell has two or three living neighbours, it stays alive.
If a living cell has more than three living neighbours, it dies.
If a dead cell has exactly three living neighbours, it becomes alive.
*/

void InitMap(Grid& a_grid)
{
	for (int x = 0; x < width; x += 10)
	{
		for (int y = 0; y < height; y += 10)
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
	for (int i = -10; i < 20; i += 10)
	{
		for (int j = -10; j < 20; j += 10)
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

const int deathLimit = 4;
const int birthLimit = 4;

/*
Perform one round of life simulation using rules. This function will modify given grid
*/
void DoSimStep(Grid& a_map)
{
	Grid newMap(width, vector<bool>(height, false));
	for (int x = 0; x < a_map.size(); x += 10)
	{
		for (int y = 0; y < a_map[0].size(); y += 10)
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

void WriteBlock(float x, float y, BMP& bitMap)
{
	RGBApixel p;
	p.Red = 0;
	p.Green = 0;
	p.Blue = 255;
	p.Alpha = 255;

	for (int i = x - 5; i < x + 5; i++)
	{
		for (int j = y - 5; j < y + 5; j++)
		{
			if (i >= 0 && i <= width && j >= 0 && j <= height)
			{
				bitMap.SetPixel(i, j, p);
			}
		}
	}
}

void MakeBitmap(Grid& cellMap, BMP& bitMap)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (cellMap[x][y])
			{
				WriteBlock(x, y, bitMap);
			}
		}
	}
}

bool operator==(const RGBApixel& lhs, const RGBApixel& rhs)
{
	if (&lhs == &rhs)
		return true;
	if (lhs.Alpha != rhs.Alpha || lhs.Blue != rhs.Blue || lhs.Green != rhs.Green || lhs.Red != rhs.Red)
		return false;
	return true;
}

bool operator!=(const RGBApixel& lhs, const RGBApixel& rhs)
{
	return !(lhs == rhs);
}



void FloodFill(Vector2& pixel, BMP& image, RGBApixel& targetColor, RGBApixel& newColor)
{


	//current node color
	RGBApixel nodeColor = image.GetPixel(pixel.x, pixel.y);

	if (targetColor == nodeColor)
		return;

	if (nodeColor == newColor)
	{
		return;
	}
	//set node to new color
	image.SetPixel(pixel.x, pixel.y, newColor);

	FloodFill(Vector2(pixel.x - 1, pixel.y), image, targetColor, newColor);
	FloodFill(Vector2(pixel.x + 1, pixel.y), image, targetColor, newColor);
	FloodFill(Vector2(pixel.x, pixel.y - 1), image, targetColor, newColor);
	FloodFill(Vector2(pixel.x, pixel.y + 1), image, targetColor, newColor);
	return;
}

void FloodFill2(Vector2& start)
{
	Vector2* cur = nullptr;
	Vector2* mark = nullptr;
	Vector2* mark2 = nullptr;

	enum DIR
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	DIR curDir, markDir, mark2Dir;
	bool backtrack, findLoop;

	cur = &start;
	
	//set to default direction
	curDir = RIGHT;


}

void FloodFillTest(BMP& image)
{
	RGBApixel newColor;
	newColor.Red = 1.0f;
	newColor.Green = 0.0f;
	newColor.Blue = 0.0f;
	newColor.Alpha = 1.0f;

	//color to search for
	RGBApixel targetColor;
	targetColor.Alpha = 1.0f;
	targetColor.Red = 1.0f;
	targetColor.Green = 1.0f;
	targetColor.Blue = 1.0f;

	//find cave
	Vector2 cavePos;
	bool found = false;
	for (int x = 0; x < width && !found; x++)
	{
		for (int y = 0; y < height && !found; y++)
		{
			if (image.GetPixel(x,y) == targetColor)
			{
				cavePos.x = x;
				cavePos.y = y;
				found = true;
			}
		}
	}



	FloodFill(cavePos, image, targetColor, newColor);

}

void main(){


	Initialise(width, height, false, "Test Game");
	SetBackgroundColour(SColour(255, 255, 255, 255));
	bool quit = false;
	int count = 0;

	//set seed
	srand(time(nullptr));
	//initalize 2d vector to false
	Grid cellMap(width, vector<bool>(height, false));
	InitMap(cellMap);

	for (int i = 0; i < 5; i++)
		DoSimStep(cellMap);



	BMP image;
	image.SetSize(width, height);
	MakeBitmap(cellMap, image);

	FloodFillTest(image);

	image.WriteToFile("myImage.bmp");
	unsigned int pixel = CreateSprite("myImage.bmp", width, height, true);

	do
	{
		MoveSprite(pixel, width * .5f, height * .5f);
		DrawSprite(pixel);

		if (IsKeyDown('Q'))
		{
			quit = true;
		}

		ClearScreen();

	} while (!FrameworkUpdate() && !quit);

	Shutdown();
	//system("pause");
}

