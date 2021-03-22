#pragma once
#ifndef _SLIME_H_
#define _SLIME_H_
#include "SpriteObject.h"
#include "Enemy.h"

class Slime : public Enemy
{
private:
	int m_maxHealth;

	int m_jumpTimer;
	

public:
	Slime(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	void Update();
	void Render();
	void AttackPattern();
	void faceDir(bool f);
	
};

#endif