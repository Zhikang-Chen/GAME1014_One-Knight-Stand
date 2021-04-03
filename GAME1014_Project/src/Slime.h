#pragma once
#ifndef _SLIME_H_
#define _SLIME_H_
#include "SpriteObject.h"
#include "Enemy.h"

class Slime final : public Enemy
{
private:
	int m_jumpTimer;
	

public:
	Slime(SDL_Rect s, SDL_FRect d);
	//void Update();
	void Move();
	bool DropTable(int r);
	
};

#endif