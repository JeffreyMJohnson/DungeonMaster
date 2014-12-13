#ifndef _WALL_H_
#define _WALL_H_
#include "Entity.h"
#include "Block.h"
#include <vector>

typedef  std::vector<Block*> BlockArray;

class Wall
	: public Entity
{
public:
	Wall();
	~Wall();
	void Update(float f_TimeDelta);
	void Draw(void);
	void Destroy(void);
	//void AddBlock(Block* a_block);
	//bool IsEmpty();
	//Block* GetBlock(const int index);
	//int Size();
private:
	BlockArray mv_BlocksList;

};
#endif