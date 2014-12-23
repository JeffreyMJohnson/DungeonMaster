
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
};