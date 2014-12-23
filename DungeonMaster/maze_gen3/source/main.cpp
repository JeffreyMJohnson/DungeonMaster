#include <iostream>
#include <time.h>
#include <assert.h>
#include <vector>

using namespace std;

struct intVec2
{
	int x, y;
	intVec2(){ x = 0; y = 0; }
	intVec2(int x, int y){ this->x = x; this->y = y; }
	intVec2 operator=(intVec2& rhs)
	{
		return intVec2(rhs.x, rhs.y);
	}
	~intVec2(){}

	intVec2 operator+(intVec2& rhs)
	{
		return intVec2(x + rhs.x, y + rhs.y);
	}
};

struct CellDirection
{
	static intVec2 north;
	static intVec2 east;
	static intVec2 south;
	static intVec2 west;
};

intVec2 CellDirection::north = intVec2(0, 1);
intVec2 CellDirection::east = intVec2(1, 0);
intVec2 CellDirection::south = intVec2(0, -1);
intVec2 CellDirection::west = intVec2(-1, 0);

struct Cell;

struct Wall
{
	Cell* cellA = nullptr;
	Cell* cellB = nullptr;
	bool isWall = true;
};

struct Cell
{
	bool isPartOfMaze = false;
	intVec2 position;
	vector<Wall*> walls;
	~Cell()
	{
		for (Wall* w : walls)
		{
			delete w;
		}
		walls.clear();
	}

	Wall* GetWall(Cell* opposite)
	{
		for (Wall* w : walls)
		{
			if (w->cellB == opposite)
				return w;
		}
		assert(true);//shouldn't get here
		return nullptr;
	}
};

const int sizeX = 20;
const int sizeY = 20;

vector<vector<Cell*>> cells;

void CreateGrid()
{
	for (int x = 0; x < sizeX; ++x)
	{
		vector<Cell*> v;
		for (int y = 0; y < sizeY; ++y)
		{
			Cell* c = new Cell;
			c->position = intVec2(x, y);
			v.push_back(c);
		}
		cells.push_back(v);
	}
}

bool IsInBounds(intVec2& position)
{
	return position.x >= 0 && position.y >= 0 && position.x < sizeX && position.y < sizeY;
}

void LoadWall(intVec2 pos, intVec2 neighborPos)
{
	if (IsInBounds(neighborPos))
	{
		Wall* w = new Wall;
		w->cellA = cells[pos.x][pos.y];
		w->cellB = cells[neighborPos.x][neighborPos.y];
		cells[pos.x][pos.y]->walls.push_back(w);
	}
}

void GenerateMaze()
{
	CreateGrid();
	for (int x = 0; x < sizeX; ++x)
	{
		for (int y = 0; y < sizeY; ++y)
		{
			intVec2 pos = intVec2(x, y);
			intVec2 neighborPos = intVec2(x, y) + CellDirection::north;
			LoadWall(pos, neighborPos);
			neighborPos = intVec2(x, y) + CellDirection::east;
			LoadWall(pos, neighborPos);
			neighborPos = intVec2(x, y) + CellDirection::south;
			LoadWall(pos, neighborPos);
			neighborPos = intVec2(x, y) + CellDirection::west;
			LoadWall(pos, neighborPos);
		}
	}
}

void PrintBottomRow(vector<Cell*>& rowToPrint)
{
	for (Cell* c : rowToPrint)
	{
		//get south wall status
		intVec2 neighborPos = c->position + CellDirection::south;
		assert(IsInBounds(neighborPos));
		Wall* w = c->GetWall(cells[neighborPos.x][neighborPos.y]);
		if (w == nullptr || w->isWall)
			cout << "_";
		else
			cout << " ";
	}
	cout << endl;
}

void PrintCenterRow(vector<Cell*>& rowToPrint)
{
	for (Cell* c : rowToPrint)
	{
		//get west wall status
		intVec2 wNeighborPos = c->position + CellDirection::west;
		Wall* westWall = nullptr;
		if (wNeighborPos.x >= 0)
			westWall = c->GetWall(cells[wNeighborPos.x][wNeighborPos.y]);

		//get east wall
		intVec2 eNeighborPos = c->position + CellDirection::east;
		Wall* eastWall = nullptr;
		if (eNeighborPos.x < sizeX)
			eastWall = c->GetWall(cells[eNeighborPos.x][eNeighborPos.y]);

		if (westWall == nullptr || westWall->isWall)
			cout << "|";
		else
			cout << " ";
		cout << " ";
		if (eastWall == nullptr || eastWall->isWall)
			cout << "|";
		else
			cout << " ";
	}
	cout << endl;
}

void PrintMaze()
{
	//top row
	for (int i = 0; i < sizeX; ++i)
	{
		cout << "_";
	}
	cout << endl;
	
	for (int x = 0; x < sizeX; ++x)
	{
		PrintCenterRow(cells[x]);
		PrintBottomRow(cells[x]);
	}
}

void main()
{
	GenerateMaze();

	PrintMaze();

	system("pause");
}

//
//
//
//enum WALLDIRECTION
//{
//	N = 0,
//	E,
//	S,
//	W
//};
//
//struct Cell;
//
////a wall is a vertice edge between 2 cells.
////the data signifies the wall is between cell1 and cell2 in the direction noted
////i.e. Wall direction = N, cell1 = [0][0], cell2 = [0][1] is N wall w respect to cell1

//
//typedef vector<Wall*> List;
//typedef List::iterator ListIt;
//
//struct Cell
//{
//	int x, y;
//	Wall* walls[4];
//	bool isPartOfMaze;
//
//	Cell()
//	{
//		x = 0;
//		y = 0;
//		isPartOfMaze = false;
//		for (int i = 0; i < 4; ++i)
//		{
//			walls[i] = nullptr;
//		}
//	}
//	Cell(int x, int y)
//	{
//		this->x = x;
//		this->y = y;
//		isPartOfMaze = false;
//		for (int i = 0; i < 4; ++i)
//		{
//			walls[i] = nullptr;
//		}
//	}
//
//	friend ostream& operator<<(ostream& out, Cell& rhs)
//	{
//		if (rhs.isPartOfMaze)
//			out << "*";
//		else
//			out << " ";
//		return out;
//	}
//};
//
//
//

//
//Cell* cells[sizeX][sizeY];
//
//void GenerateMaze()
//{
//	for (int x = 0; x < sizeX; ++x)
//	{
//		for (int y = 0; y < sizeY; ++y)
//		{
//			cells[x][y] = new Cell(x, y);
//		}
//	}
//
//	//loop again because assigning cells for the walls might not be created yet during prev loop
//	//must be better way
//
//	for (int x = 0; x < sizeX; ++x)
//	{
//		for (int y = 0; y < sizeY; ++y)
//		{
//			Wall* neighborWalls[4];
//			Wall* nWall = new Wall;
//			Wall* eWall = new Wall;
//			Wall* sWall = new Wall;
//			Wall* wWall = new Wall;
//			int eX = x + 1;
//			int wX = x - 1;
//			int nY = y + 1;
//			int sY = y - 1;
//
//			eWall->direction = E;
//			if (eX < sizeX)
//			{
//				eWall->neighborCell = cells[eX][y];
//			}
//			else
//				eWall->neighborCell = nullptr;
//
//			wWall->direction = W;
//			if (wX >= 0)
//				wWall->neighborCell = cells[wX][y];
//			else
//				wWall->neighborCell = nullptr;
//
//			nWall->direction = N;
//			if (nY < sizeY)
//				nWall->neighborCell = cells[x][nY];
//			else
//				nWall->neighborCell = nullptr;
//
//			sWall->direction = S;
//			if (sY >= 0)
//				sWall->neighborCell = cells[x][sY];
//			else
//				sWall->neighborCell = nullptr;
//
//			cells[x][y]->walls[N] = nWall;
//			cells[x][y]->walls[E] = eWall;
//			cells[x][y]->walls[S] = sWall;
//			cells[x][y]->walls[W] = wWall;
//		}
//	}
//
//}
//
//void DestroyMaze()
//{
//	for (int x = 0; x < sizeX; ++x)
//	{
//		for (int y = 0; y < sizeY; ++y)
//		{
//			Cell* c = cells[x][y];
//			for (int i = 0; i < 4; ++i)
//			{
//				delete c->walls[i];
//			}
//			delete c;
//		}
//	}
//}
//
//void PrintMaze()
//{
//	for (int x = 0; x < sizeX; ++x)
//	{
//		for (int y = 0; y < sizeY; ++y)
//		{
//			cout << *cells[x][y];
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//
//int GetRand(int min, int max)
//{
//	int r = (rand() % (max - min + 1)) + min;
//	assert(r >= min);
//	assert(r <= max);
//	return r;
//}
//
//Cell* PickRandCell()
//{
//	int x = GetRand(0, sizeX);
//	int y = GetRand(0, sizeY);
//	return cells[x][y];
//}
//
//
//
//void main()
//{
//	srand(time(NULL));
//	GenerateMaze();
//	PrintMaze();
//
//	//pick a cell
//	Cell* pickedCell = cells[0][0];
//
//	//mark as part of maze
//	pickedCell->isPartOfMaze = true;
//
//	//add walls of cell to wall list
//	List wallList;
//	for (int i = 0; i < 4; ++i)
//	{
//		if (pickedCell->walls[i]->neighborCell != nullptr)
//		{
//			wallList.push_back(pickedCell->walls[i]);
//		}
//	}
//
//	int count = 0;
//	while (wallList.size() > 0 || count < sizeX * sizeY)
//	{
//		//pick random wall from list
//		int index = GetRand(0, wallList.size() - 1);
//		ListIt it = wallList.begin() + index;
//		Wall* pickedWall = wallList[index];
//
//		//is cell on opposite side in maze?
//		if (!pickedWall->neighborCell->isPartOfMaze)
//		{
//			Cell* neighborCell = pickedWall->neighborCell;
//
//			//mark opposite cell part of maze
//			neighborCell->isPartOfMaze = true;
//
//			//make wall passage
//			pickedWall = nullptr;
//
//			//add neighboring walls to wall list
//			for (int i = 0; i < 4; ++i)
//			{
//				Wall* wall = neighborCell->walls[i];
//				if (wall != nullptr && wall->neighborCell != nullptr)
//				{
//					wallList.push_back(wall);
//				}
//			}
//
//
//
//			//remove from walllist
//			wallList.erase(it);
//
//			
//		}
//
//		count++;
//	}
//
//	DestroyMaze();
//}
//
