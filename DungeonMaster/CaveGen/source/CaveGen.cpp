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

const float chanceToStartAlive =20.0f;
const float chanceToLive = 0.45f;

/*
rules:
If a living cell has less than two living neighbours, it dies.
If a living cell has two or three living neighbours, it stays alive.
If a living cell has more than three living neighbours, it dies.
If a dead cell has exactly three living neighbours, it becomes alive.
*/


//Grid DoSimStep(Grid& a_grid)
//{
//
//}

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

	unsigned int pixel = CreateSprite("images/pixel_10.png", 10, 10, true);
	//MoveSprite(pixel, width * .25, height - 100);
	do
	{
		SetFont("./fonts/invaders.fnt");
		DrawString("FOO Mother Fucker!", width * 0.5f, height * 0.5f);
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
		if (count == 10000)
			quit = true;
		else
			count++;
		ClearScreen();
	} while (!FrameworkUpdate() && !quit);



	Shutdown();
	//system("pause");
}

