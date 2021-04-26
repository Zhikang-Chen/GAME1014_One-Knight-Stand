#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "SpriteObject.h"


class Projectile : public AnimatedSpriteObject
{
public:
	Projectile(SDL_Rect s, SDL_FRect d, SDL_Texture* t, SDL_FPoint tr = {0,0});
	void Update() override = 0;
	void Render() override = 0;

	const SDL_FPoint GetTarget();
	void SetTarget(SDL_FPoint t);
	void SetTarget(float x, float y);

protected:
	SDL_FPoint m_target;
};

#endif
