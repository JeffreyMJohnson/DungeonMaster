#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <string>
#include "AIE.h"
#include "TheMath.h"

class Entity
{
public:
	virtual void Init(std::string s_fileName, const float a_f_Width, const float a_f_Height)
	{
		mui_SpriteID = CreateSprite(s_fileName.c_str(), a_f_Width, a_f_Height, true);
		mf_Width = a_f_Width;
		mf_Height = a_f_Height;
	}
	virtual void Update(float f_TimeDelta) = 0;
	virtual void Draw(void) = 0;
	virtual void Destroy(void) = 0;
	Vector2 mv_Position;
protected:
	float mf_Width, mf_Height;
	unsigned int mui_SpriteID;

};
#endif