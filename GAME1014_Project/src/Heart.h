#pragma once
#ifndef _HEART_H_
#define _HEART_H_
#include "SpriteObject.h"

class Heart : public SpriteObject
{
public:
	Heart(SDL_Rect s, SDL_FRect d);
	void SetEmpty(bool e);
	bool GetEmpty();
private:
	bool m_empty;
	void Update() {};
	void Render();
};

#endif

