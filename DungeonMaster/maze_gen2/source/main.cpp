#include <vector>
#include <time.h>
#include "TheMath.h"

using namespace std;

typedef vector<Vector2> Vec2List;
typedef vector<vector<bool>> Bool2DList;
typedef Vector2 vec2;

Bool2DList g_IsWallList;
Bool2DList g_IsPartOfMazeList;
Vec2List g_WallList;

int gridWidth = 10;
int gridHeight = 10;

//needed to use in map


void InitList()
{
	for (int x = 0; x < gridWidth; ++x)
	{
		vector<bool> t;
		vector<bool> f;
		for (int y = 0; y < gridHeight; ++y)
		{
			t.push_back(true);
			f.push_back(false);
		}
		g_IsWallList.push_back(t);
		g_IsPartOfMazeList.push_back(f);
	}
}

vec2 GetRandomCell()
{
	int x = rand() % gridWidth;
	int y = rand() % gridHeight;
	return vec2(x, y);
}

void AddWallsToList(vec2& cell)
{
	vec2 n = vec2(cell.x, cell.y + 1);
	vec2 s = vec2(cell.x, cell.y - 1);
	vec2 e = vec2(cell.x + 1, cell.y);
	vec2 w = vec2(cell.x - 1, cell.y);

	//is cell in bounds and a wall
	if (n.x < gridHeight && g_IsWallList[n.x][n.y])
	{
		g_WallList.push_back(n);
	}
	if (s.x >= 0 && g_IsWallList[s.x][s.y])
	{
		g_WallList.push_back(s);
	}
	if (e.x < gridWidth && g_IsWallList[e.x][e.y])
	{
		g_WallList.push_back(e);
	}
	if (w.x >= 0 && g_IsWallList[w.x][w.y])
	{
		g_WallList.push_back(w);
	}
}

void main()
{
	srand(time(nullptr));
	InitList();
	vec2 firstCell = GetRandomCell();
	g_IsPartOfMazeList[firstCell.x][firstCell.y] = true;

	AddWallsToList(firstCell);

	while (!g_WallList.empty())
	{

	}

	system("pause");
}