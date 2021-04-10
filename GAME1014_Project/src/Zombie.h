#pragma once
#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_
#include "SpriteObject.h"
#include "Enemy.h"



class Zombie final : public Enemy
{
public:
	Zombie(SDL_Rect s, SDL_FRect d);
	//void Update();
	void Move();
	bool DropTable(int r);

	int m_zSoundCount = 0;
};

#endif