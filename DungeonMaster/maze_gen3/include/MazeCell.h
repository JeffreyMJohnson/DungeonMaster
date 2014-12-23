#include "intVec2.h"

class MazeCell
{
public:
	intVec2 position;

	MazeCell(){ position = intVec2(); }
	MazeCell(int x, int y){ position = intVec2(x, y); }
	MazeCell(intVec2 position){	this->position = position; }
	~MazeCell(){};
private:

};