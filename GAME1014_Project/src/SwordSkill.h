#pragma once
#ifndef _SWORDSKILL_H_
#define _SWORDSKILL_H_
#include "SpriteObject.h"

class SwordSkill : public SpriteObject
{
public:
	SwordSkill(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	void Update() ;
	void Render();
};

#endif

