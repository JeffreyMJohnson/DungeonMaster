#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <assert.h>

using namespace std;

const int gi_GridWidth = 10;
const int gi_GridHeight = 10;












Grid gg_Maze(gi_GridWidth, gi_GridHeight);
vector<Cell*> vcp_WallList;
Cell* PickCell();

void main()
{
	srand(time(nullptr));

	Cell* cp_FirstCell = PickCell();
	cp_FirstCell->isPartOfMaze = true;

	//add walls of cell to wall list
	vector<Cell*> walls = cp_FirstCell->GetNeighborWalls();
	for (Cell* c : walls)
	{
		vcp_WallList.push_back(c);
	}

	system("pause");

}




ostream& operator<<(ostream& out, Cell& rhs)
{
	out << "Cell: [position: " << rhs.position;
	out << " previous: " << rhs.previous;
	out << " isPartOfMaze: " << rhs.isPartOfMaze;
	out << " isPassage: " << rhs.isPassage;
	out << "]";
	return out;
}

ostream& operator<<(ostream& out, vec2& rhs)
{
	out << "vec2 [x: " << rhs.x;
	out << " y: " << rhs.y;
	out << "]";
	return out;
}
bool operator==(const vec2& lhs, const vec2& rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

Cell* PickCell()
{
	int i_randX = rand() % gi_GridWidth;
	int i_randY = rand() % gi_GridHeight;
	Cell* c = gg_Maze.GetCell(vec2(i_randX, i_randY));
	assert(c != nullptr);
	return c;
}