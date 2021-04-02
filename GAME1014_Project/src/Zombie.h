#pragma once
#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_
#include "SpriteObject.h"
#include "Enemy.h"



class Zombie : public Enemy
{
private: 
	int m_maxHealth;

public:
	Zombie(SDL_Rect s, SDL_FRect d);
	//void Update();
	void Render();
	void Move();
};

#endif