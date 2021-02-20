#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "SpriteObject.h"

class Background : public SpriteObject
{
public:
	Background(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	void Update(){};
	void Render();
};

#endif

