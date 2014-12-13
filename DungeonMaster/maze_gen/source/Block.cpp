#include "Block.h"

Block::Block()
{

}

Block::~Block()
{

}
void Block::Update(float f_TimeDelta)
{
	MoveSprite(mui_SpriteID, mv_Position.x, mv_Position.y);
}
void Block::Draw(void)
{
	DrawSprite(mui_SpriteID);
}
void Block::Destroy(void)
{

}