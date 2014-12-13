#include "Wall.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}
void Wall::Update(float f_TimeDelta)
{
	MoveSprite(mui_SpriteID, mv_Position.x, mv_Position.y);
	//for (Block* block : mv_BlocksList)
	//{
	//	block->Update(f_TimeDelta);
	//}
}
void Wall::Draw(void)
{
	DrawSprite(mui_SpriteID);
	//for (Block* block : mv_BlocksList)
	//{
	//	block->Draw();
	//}
}
void Wall::Destroy(void)
{
	//for (auto block : mv_BlocksList)
	//{
	//	delete block;
	//}
	//mv_BlocksList.clear();
}

//void Wall::AddBlock(Block* a_block)
//{
//	mv_BlocksList.push_back(a_block);
//}
//bool Wall::IsEmpty()
//{
//	return mv_BlocksList.empty();
//}
//Block* Wall::GetBlock(const int index)
//{
//	return mv_BlocksList[index];
//}
//int Wall::Size()
//{
//	return mv_BlocksList.size();
//}