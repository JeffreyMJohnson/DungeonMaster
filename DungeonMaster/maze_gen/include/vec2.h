#ifndef _VEC2_H_
#define _VEC2_H_
#include <iostream>

struct vec2
{
	int x, y;
	vec2()
	{
		x = 0;
		y = 0;
	}
	vec2(const int x, const int y)
	{
		this->x = x;
		this->y = y;
	}
	vec2(const vec2& other)
	{
		x = other.x;
		y = other.y;
	}
	vec2& operator=(const vec2& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	bool operator==(const vec2& rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}
	bool operator!=(const vec2& rhs)
	{
		return !(*this == rhs);
	}
	friend std::ostream& operator<<(std::ostream& out, vec2& rhs);
	friend bool operator==(const vec2& lhs, const vec2& rhs);
};

#endif