#pragma once
#include "SpriteObject.h"

class Potion : public AnimatedSpriteObject
{
private:
	bool m_facingLeft = false;

protected:

public:
	Potion(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	void Render();
};