#pragma once
#ifndef _BULLET_H_
#define __BULLET_H_

#include "EntityObject.h"

class Bullet : public EntityObject
{
private:

public:
	Bullet(SDL_Rect s, SDL_FRect d, SDL_Texture* t);

	void Update();
	void Render();
};
#endif
