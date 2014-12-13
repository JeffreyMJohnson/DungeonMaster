#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "Entity.h"

class Block
	: public Entity
{
public:
	Block();
	~Block();
	void Update(float f_TimeDelta);
	void Draw(void);
	void Destroy(void);
protected:

};
#endif