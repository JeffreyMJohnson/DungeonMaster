#include <vector>

#include "MazeCell.h"

using namespace std;

typedef vector<vector<MazeCell*>> MazeCellList;

class Maze
{
public:
	int sizeX, sizeY;

	Maze(){ sizeX = 0; sizeY = 0; }
	Maze(int sizeX, int sizeY)
	{
		this->sizeX = sizeX; 
		this->sizeY = sizeY; 
	
	}
	~Maze()
	{
		for (int x = 0; x < cells.size(); ++x)
		{
			for (int y = 0; y < cells[x].size(); ++y)
			{
				delete cells[x][y];
			}
		}
		cells.clear();
	}

	void CreateCell(int x, int y)
	{
		
	}

	void Generate()
	{
		for (int x = 0; x < cells.size(); ++x)
		{
			for (int y = 0; y < cells[x].size(); ++y)
			{
				//MazeCell* newCell = new MazeCell(x,y);
				//cells[x]
			}
		}
	}




private:
	MazeCellList cells;
};