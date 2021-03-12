#pragma once
#ifndef _SLIME_H_
#define _SLIME_H_
#include "SpriteObject.h"
#include "Enemy.h"

class Slime : public Enemy
{
private:
	int m_maxHealth = 5;

public:
	Slime(SDL_Point p);
};

#endif