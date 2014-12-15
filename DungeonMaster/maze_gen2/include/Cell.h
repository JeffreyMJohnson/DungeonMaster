#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include "TheMath.h"

typedef Vector2 vec2;

enum DIRECTION
{
	N,S,E,W
};

class Cell
{
public:
	DIRECTION moveDirection;
	vec2 position;
	bool isPartOfMaze;
	bool isPassage;
	Cell* GetOpposite(std::vector<std::vector<Cell*>>& a_grid, int width, int height);
	std::vector<Cell*> GetNeighborWalls(std::vector<std::vector<Cell*>>& a_CellGrid, int width, int height);

	Cell();
	~Cell(){};
	friend std::ostream& operator<<(std::ostream& out, Cell& rhs);
};


#endif