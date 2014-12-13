#ifndef _GRID_H_
#define _GRID_H_
#include <vector>
#include <assert.h>
#include <vector>

#include "Cell.h"

class Grid
{
public:
	Grid();
	Grid(const int width, const int height);
	~Grid();
	Cell* GetCell(const vec2& gridPosition);

	int GetSize();

	int GetWidth();

	int GetHeight();

	friend std::ostream& operator<<(std::ostream& out, Grid& rhs);

protected:
	std::vector<Cell*> mv_CellGrid;
	int mi_Width, mi_Height;
};


#endif