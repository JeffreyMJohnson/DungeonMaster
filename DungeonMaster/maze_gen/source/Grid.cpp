#include "Grid.h"

Grid::Grid()
	{
		Grid(100, 100);
	}
Grid::Grid(const int width, const int height)
	{
		mi_Width = width;
		mi_Height = height;
		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				Cell* c = new Cell;
				c->position = vec2(x, y);
				mv_CellGrid.push_back(c);
			}
		}
	}
Grid::~Grid()
	{
		for (int x = 0; x < mi_Width; ++x)
		{
			for (int y = 0; y < mi_Height; ++y)
			{
				vec2 pos(x, y);
				Cell* c = GetCell(pos);
				assert(c != nullptr);
				delete c;
			}
		}
	}
Cell* Grid::GetCell(const vec2& gridPosition)
	{
		//assert(gridPosition.x < gi_GridWidth);
		//assert(gridPosition.y < gi_GridHeight);
		return mv_CellGrid[((gridPosition.x * mi_Height) + gridPosition.y)];


		//mi_CellGridIt result = find(mv_CellGrid.begin(), mv_CellGrid.end(), gridPosition);
		//if (result == mv_CellGrid.end())
		//	return nullptr;
		//return *result;

	}

int Grid::GetSize()
	{
		return mv_CellGrid.size();
	}

int Grid::GetWidth()
{
	return mi_Width;
}

int Grid::GetHeight()
{
	return mi_Height;
}

std::ostream& operator<<(std::ostream& out, Grid& rhs)
{
	std::string s = "Grid:\n[\n";
	for (int x = 0; x < rhs.mi_Width; ++x)
	{
		out << "row: " << x + 1 << "\n";
		for (int y = 0; y < rhs.mi_Width; ++y)
		{
			Cell* c = rhs.GetCell(vec2(x, y));
			assert(c != nullptr);
			out << *c;
			out << '\n';
		}
		out << "\n\n";
	}
	out << "]";
	return out;
}