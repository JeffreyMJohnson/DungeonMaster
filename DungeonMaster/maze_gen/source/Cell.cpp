#include "Cell.h"

Cell::Cell()
{
	previous = nullptr;
	isPartOfMaze = false;
	isPassage = false;
}

vec2 Cell::GetOpposite()
{
	//use prev pos and current to get direction
	if (position.y == previous->position.y)
	{
		return vec2(position.x + (position.x - previous->position.x), position.y);
		//int deltaX = position.x - previous->position.x;
		////east?
		//if (deltaX < 0)
		//{
		//	return vec2(position.x - 1, position.y);
		//}
		//else
		//{
		//	return vec2(position.x + 1, position.y);
		//}
	}
	else
	{
		return vec2(position.y, position.y - (position.y - previous->position.y));
	}
}
std::vector<Cell*> Cell::GetNeighborWalls(const Grid& a_grid)
{
	std::vector<Cell*> result;
	vec2 n(position.x, position.y + 1);
	vec2 s(position.x, position.y - 1);
	vec2 e(position.x - 1, position.y);
	vec2 w(position.x + 1, position.y);

	if (n.x >= 0 && n.x < a_grid.GetWidth() && !gg_Maze.GetCell(n)->isPassage)
	{
		result.push_back(gg_Maze.GetCell(n));
	}
	if (s.x >= 0 && s.x < a_grid.GetWidth() && !gg_Maze.GetCell(s)->isPassage)
	{
		result.push_back(gg_Maze.GetCell(s));
	}
	if (e.x >= 0 && e.x < a_grid.GetHeight() && !gg_Maze.GetCell(e)->isPassage)
	{
		result.push_back(gg_Maze.GetCell(e));
	}
	if (w.x >= 0 && w.x < a_grid.GetHeight() && !gg_Maze.GetCell(w)->isPassage)
	{
		result.push_back(gg_Maze.GetCell(w));
	}
	return result;
}
