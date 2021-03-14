#pragma once
#ifndef _SLIME_H_
#define _SLIME_H_
#include "SpriteObject.h"
#include "Enemy.h"

class Slime : public Enemy
{
private:
	int m_maxHealth = 1;

public:
	Slime(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	~Slime();
	void Update();
	void Render();
	void AttackPattern();
};

#endif