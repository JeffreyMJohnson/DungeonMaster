#include <iostream>
#include <time.h>
#include <assert.h>
#include <vector>

#include "intVec2.h"

using namespace std;

const int sizeX = 20;
const int sizeY = 20;

struct Wall
{
	enum DIRECTION
	{
		N = 0,
		E,
		S,
		W
	};
	bool isWall = true;
	intVec2 otherSide = intVec2(-1, -1);

	Wall& operator=(Wall& rhs)
	{
		this->isWall = rhs.isWall;
		this->otherSide = rhs.otherSide;
		return *this;
	}

	friend ostream& operator<<(ostream& out, Wall& rhs)
	{
		out << "Wall: [isWall: " << rhs.isWall;
		out << " otherSide: " << rhs.otherSide;
		out << "]";
		return out;
	}

};

struct Cell
{
	bool isInMaze = false;
	intVec2 position;
	Wall walls[4];

	Cell& operator=(Cell& rhs)
	{
		this->isInMaze = rhs.isInMaze;
		this->position = rhs.position;
		memcpy(this->walls, rhs.walls, sizeof(Wall) * 4);
		return *this;
	}

	friend ostream& operator<<(ostream& out, Cell& rhs)
	{
		out << "Cell: [isInMaze: " << rhs.isInMaze;
		out << " position: " << rhs.position;
		for (int i = 0; i < 4; i++)
		{
			switch ((Wall::DIRECTION)i)
			{
			case Wall::N:
				out << " N ";
				break;
			case Wall::E:
				out << " E ";
				break;
			case Wall::S:
				out << " S ";
				break;
			case Wall::W:
				out << " W ";
				break;
			}
			out << "wall: " << rhs.walls[(Wall::DIRECTION)i];
		}
		return out;
	}
};

Cell cells[sizeX][sizeY];

bool IsInBounds(intVec2& position);

void InitializeGrid();

void GenerateMaze();

void GenerateCellWalls(Cell& cell);

void PrintMaze();

void AddWallsToWallList(vector<Wall*>& wallList, Cell& cell);

int GetRand(int min, int max);

void main()
{
	InitializeGrid();
	GenerateMaze();
	PrintMaze();
	system("pause");
}

bool IsInBounds(intVec2& position)
{
	return position.x >= 0 && position.y >= 0 && position.x < sizeX && position.y < sizeY;
}

void InitializeGrid()
{
	for (int x = 0; x < sizeX; ++x)
	{
		for (int y = 0; y < sizeY; ++y)
		{
			cells[x][y].position = intVec2(x, y);
			GenerateCellWalls(cells[x][y]);
		}
	}
}

void GenerateMaze()
{
	//pick a cell
	intVec2 pickedCellPos(0, 0);
	//use macro for readability
#define pickedCell cells[pickedCellPos.x][pickedCellPos.y]

	//mark as part of maze
	pickedCell.isInMaze = true;
	//add walls of cell to wall list
	vector<Wall*> wallList;
	AddWallsToWallList(wallList, pickedCell);

	while (!wallList.empty())
	{
		//pick random wall from list
		//int randomWallListIndex = GetRand(0, wallList.size() - 1);
		//Wall pickedWall = wallList[randomWallListIndex];
		//debug
		//Wall pickedWall = wallList.back();

		//is cell on opposite side in maze?
		//use macro for readability
		#define oppositeCell cells[wallList.back()->otherSide.x][wallList.back()->otherSide.y]
		//check if this is boundary wall where the oppositie side is out of  bounds
		bool isOppositeCellOutOfBounds = false;
		if (wallList.back()->otherSide.x < 0 || wallList.back()->otherSide.y < 0)
			isOppositeCellOutOfBounds = true;
		if (!isOppositeCellOutOfBounds && !oppositeCell.isInMaze)
		{
			//make wall a passage;
			wallList.back()->isWall = false;
			//mark cell on opposite side as part of maze
			oppositeCell.isInMaze = true;
			//add neighboring walls of the cell to the list
			AddWallsToWallList(wallList, oppositeCell);
		}
		//remove the wall from the list
		//debug
		wallList.pop_back();
	}

}

void GenerateCellWalls(Cell& cell)
{
	if (IsInBounds(cell.position + intVec2::north))
		cell.walls[Wall::N].otherSide = cell.position + intVec2::north;
	if (IsInBounds(cell.position + intVec2::east))
		cell.walls[Wall::E].otherSide = cell.position + intVec2::east;
	if (IsInBounds(cell.position + intVec2::south))
		cell.walls[Wall::S].otherSide = cell.position + intVec2::south;
	if (IsInBounds(cell.position + intVec2::west))
		cell.walls[Wall::W].otherSide = cell.position + intVec2::west;
}

void PrintSouthWallRow(int rowIndex)
{
	for (int y = 0; y < sizeY; ++y)
		{
			if (cells[rowIndex][y].walls[Wall::S].isWall)
				cout << "_";
			else
				cout << " ";
		}
}

void PrintNorthWallRow(int rowIndex)
{
	for (int y = 0; y < sizeY; ++y)
	{
		if (cells[rowIndex][y].walls[Wall::N].isWall)
			;
	}
}

void PrintMaze()
{
	for (int i = 0; i < sizeX; i++)
	{
		PrintSouthWallRow(i);
	}
}

void AddWallsToWallList(vector<Wall*>& wallList, Cell& cell)
{
	for (int i = 0; i < 4; i++)
	{
		if (cell.walls[i].isWall)
			wallList.push_back(&cell.walls[i]);
	}
}

int GetRand(int min, int max)
{
	int r = (rand() % (max - min + 1)) + min;
	assert(r >= min);
	assert(r <= max);
	return r;
}