#include "Cell.h"

Cell::Cell()
{
	moveDirection = N;
	isPartOfMaze = false;
	isPassage = false;
}

std::wostream& operator<<(std::wostream& out, Vector2& rhs)
{
	out << "Vector2 [x: " << rhs.x << " y: " << rhs.y << "]";
	return out;
}

Cell* Cell::GetOpposite(std::vector<std::vector<Cell*>>& a_grid, int width, int height)
{
	vec2 v;
	Cell* result = nullptr;
	switch (moveDirection)
	{
	case N:
		v = vec2(position.x, position.y + 1);
		if (v.y < height)
			result = a_grid[v.x][v.y];
		break;
	case S:
		v = vec2(position.x, position.y - 1);
		if (v.y > 0)
			result = a_grid[v.x][v.y];
		break;
	case E:
		v = vec2(position.x + 1, position.y);
		if (v.x < width)
			result = a_grid[v.x][v.y];
		break;
	case W:
		v = vec2(position.x - 1, position.y);
		if (v.x > 0)
			result = a_grid[v.x][v.y];
		break;
	default:
		assert(true);//should never get here
	}
	return result;
}

std::vector<Cell*> Cell::GetNeighborWalls(std::vector<std::vector<Cell*>>& a_grid, int width, int height)
{
	std::vector<Cell*> result;
	vec2 n(position.x, position.y + 1);
	vec2 s(position.x, position.y - 1);
	vec2 e(position.x + 1, position.y);
	vec2 w(position.x - 1, position.y);

	if (n.x < width && !a_grid[n.x][n.y]->isPassage)
	{
		a_grid[n.x][n.y]->moveDirection = N;
		result.push_back(a_grid[n.x][n.y]);
	}
	if (s.x >= 0 && !a_grid[s.x][s.y]->isPassage)
	{
		a_grid[s.x][s.y]->moveDirection = S;
		result.push_back(a_grid[s.x][s.y]);
	}
	if (e.x < height && !a_grid[e.x][e.y]->isPassage)
	{
		a_grid[e.x][e.y]->moveDirection = E;
		result.push_back(a_grid[e.x][e.y]);
	}
	if (w.x >= 0 && !a_grid[w.x][w.y]->isPassage)
	{
		a_grid[w.x][w.y]->moveDirection = W;
		result.push_back(a_grid[w.x][w.y]);
	}
	return result;
}

std::ostream& operator<<(std::ostream& out, Cell& rhs)
{
	out << "Cell: [isPartOfMaze: " << rhs.isPartOfMaze;
	out << ", isPassage: " << rhs.isPassage;
	out << "]";
	return out;
}