#pragma once
#ifndef _HEART_H_
#define _HEART_H_
#include "SpriteObject.h"

class Heart : public SpriteObject
{
public:
	Heart(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	void Update() {};
	void Render();
};

#endif

