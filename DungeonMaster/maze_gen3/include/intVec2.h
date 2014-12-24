#ifndef _INT_VEC_2_H_
#define _INT_VEC_2_H_

#include <iostream>

struct intVec2
{
	int x, y;
	intVec2(){ x = 0; y = 0; }
	intVec2(int x, int y){ this->x = x; this->y = y; }
	intVec2& operator=(intVec2& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	~intVec2(){}

	intVec2 operator+(intVec2& rhs)
	{
		return intVec2(x + rhs.x, y + rhs.y);
	}

	friend std::ostream& operator<<(std::ostream& out, intVec2& rhs)
	{
		out << "intVector2 [x: " << rhs.x;
		out << " y: " << rhs.y;
		out << "]";
		return out;
	}

	static intVec2 north;
	static intVec2 east;
	static intVec2 south;
	static intVec2 west;
};

intVec2 intVec2::north = intVec2(0, 1);
intVec2 intVec2::east = intVec2(1, 0);
intVec2 intVec2::south = intVec2(0, -1);
intVec2 intVec2::west = intVec2(-1, 0);

#endif