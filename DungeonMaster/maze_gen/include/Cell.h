#ifndef _CELL_H_
#define _CELL_H_
#include "Grid.h"
#include "vec2.h"
#include <iostream>
#include <vector>

class Cell
{
public:
	Cell* previous;
	vec2 position;
	bool isPartOfMaze;
	bool isPassage;
	vec2 GetOpposite();
	std::vector<Cell*> GetNeighborWalls(const Grid& a_grid);

	Cell();
	~Cell(){};
	friend std::ostream& operator<<(std::ostream& out, Cell& rhs);
};


#endif