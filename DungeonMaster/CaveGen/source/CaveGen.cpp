#include <string>
#include <vector>
#include <limits>
#include <queue>
#include <stack>
#include <time.h>
#include <iostream>
#include <assert.h>
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

void WriteBlock(float x, float y, BMP& bitMap, RGBApixel& color)
{
	for (int i = x - 5; i < x + 5; i++)
	{
		for (int j = y - 5; j < y + 5; j++)
		{
			if (i >= 0 && i < width && j >= 0 && j < height)
			{
				bitMap.SetPixel(i, j, color);
			}
		}
	}
}

void MakeBitmap(Grid& cellMap, BMP& bitMap)
{
	RGBApixel blue;
	blue.Red = 0;
	blue.Green = 0;
	blue.Blue = 255;
	blue.Alpha = 255;

	RGBApixel white;
	white.Red = 255;
	white.Green = 255;
	white.Blue = 255;
	white.Alpha = 255;

	for (int x = 0; x < width; x += 10)
	{
		for (int y = 0; y < height; y += 10)
		{
			if (cellMap[x][y])
			{
				WriteBlock(x, y, bitMap, blue);
			}
			else
			{
				WriteBlock(x, y, bitMap, white);
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

//bool IsProcessed(Vector2& pos, bool (*proceesedArray)[width][height])
//{
//	//if out of bounds return true
//	if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
//		return true;
//	bool r = proceesedArray[(int)pos.x] + (int)pos.y;
//	return r;
//}

bool InBounds(Vector2& pos)
{
	return (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height);
}

void FloodFill(Vector2& seed, BMP& image, RGBApixel& targetColor, RGBApixel& newColor)
{
	bool processed[width][height];
	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < height; col++)
		{
			processed[row][col] = false;
		}
	}

	stack<Vector2> q;
	q.push(seed);
	while (!q.empty())
	{
		Vector2 n = q.top();
		q.pop();
		RGBApixel currentPix = image.GetPixel(n.x, n.y);
		if (currentPix == targetColor)
		{
			image.SetPixel(n.x, n.y, newColor);
			processed[(int)n.x][(int)n.y] = true;

			currentPix = image.GetPixel(n.x, n.y);

			Vector2 west(n.x - 1, n.y);
			if (InBounds(west) && !processed[(int)west.x][(int)west.y])
			{
				q.push(west);
			}

			Vector2 east(n.x + 1, n.y);
			if (InBounds(east) && !processed[(int)east.x][(int)east.y])
			{
				q.push(east);
			}

			Vector2 north(n.x, n.y+1);
			if (InBounds(north) && !processed[(int)north.x][(int)north.y])
			{
				q.push(north);
			}

			Vector2 south(n.x, n.y - 1);
			if (InBounds(south) && !processed[(int)south.x][(int)south.y])
			{
				q.push(south);
			}
		}

	}

	return;
}

void FloodFillTest(BMP& image)
{
	RGBApixel newColor;
	newColor.Red = 255;
	newColor.Green = 0;
	newColor.Blue = 0;
	newColor.Alpha = 255;

	//color to search for
	RGBApixel targetColor;
	targetColor.Alpha = 255;
	targetColor.Red = 255;
	targetColor.Green = 255;
	targetColor.Blue = 255;

	//find cave
	Vector2 cavePos;
	bool found = false;
	for (int x = 0; x < width && !found; x++)
	{
		for (int y = 0; y < height && !found; y++)
		{
			if (image.GetPixel(x, y) == targetColor)
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
	image.SetBitDepth(8);
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

