#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>
#include <vector>
#include "TheMath.h"

typedef Vector2 vec2;

class Cell
{
public:
	Cell* previous;
	vec2 position;
	bool isPartOfMaze;
	bool isPassage;
	vec2 GetOpposite();
	std::vector<Cell*> GetNeighborWalls();

	Cell();
	~Cell(){};
	friend std::ostream& operator<<(std::ostream& out, Cell& rhs);
};


#endif