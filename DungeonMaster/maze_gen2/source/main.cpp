#include <vector>
#include <time.h>
#include <exception>
#include <iostream>
#include <string>
#include "TheMath.h"
#include "Cell.h"

using namespace std;

typedef vector<Cell*> Vec2List;
typedef Vec2List::iterator Vec2It;
typedef vector<vector<bool>> Bool2DList;
typedef Vector2 vec2;
typedef vector<vector<Cell*>> CellGrid;

Bool2DList g_IsWallList;
Bool2DList g_IsPartOfMazeList;
Vec2List g_WallList;

CellGrid g_CellGrid;

int gridWidth = 10;
int gridHeight = 10;

//needed to use in map


void InitList()
{
	for (int x = 0; x < gridWidth; ++x)
	{
		vector<Cell*> v;
		for (int y = 0; y < gridHeight; ++y)
		{
			Cell* c = new Cell;
			c->position = vec2(x, y);
			v.push_back(c);
		}
		g_CellGrid.push_back(v);
	}
}

Cell* GetRandomCell()
{
	int x = rand() % gridWidth;
	int y = rand() % gridHeight;
	return g_CellGrid[x][y];
}

void AddNeighboringWallsToList(Cell* cell)
{
	vector<Cell*> currentWalls = cell->GetNeighborWalls(g_CellGrid, gridWidth, gridHeight);
	for (Cell* c : currentWalls)
	{
		g_WallList.push_back(c);
	}
}

void DestroyList()
{
	for (int x = 0; x < gridWidth; ++x)
	{
		for (int y = 0; y < gridHeight; ++y)
		{
			delete g_CellGrid[x][y];
		}
		g_CellGrid.clear();
	}
}

void ToString()
{
	cout << "CellList:\n";
	cout << "************************************************************************\n";
	for (int x = 0; x < gridWidth; ++x)
	{
		cout << "row[" << x << "]:";
		for (int y = 0; y < gridHeight; ++y)
		{
			cout << "[" << y << "] - ";
			cout << *(g_CellGrid[x][y]) << endl;
		}
		cout << endl;
	}
	cout << "************************************************************************\n";
}

void main()
{
	srand(time(nullptr));
	InitList();
	Cell* firstCell = GetRandomCell();

	firstCell->isPartOfMaze = true;
	AddNeighboringWallsToList(firstCell);

	while (!g_WallList.empty())
	{
		//ToString();
		//system("pause");
		int index = rand() % g_WallList.size();
		Cell* wallFromList = g_WallList[index];

		Cell* cellOnOppositeSide = wallFromList->GetOpposite(g_CellGrid, gridWidth, gridHeight);
		if (cellOnOppositeSide != nullptr && !cellOnOppositeSide->isPartOfMaze)
		{
			wallFromList->isPassage = true;
			cellOnOppositeSide->isPartOfMaze = true;

			AddNeighboringWallsToList(wallFromList);
		}
		Vec2It wallsListIterator = g_WallList.begin();
		g_WallList.erase(wallsListIterator + index);
	}
	ToString();
	system("pause");
	DestroyList();

}