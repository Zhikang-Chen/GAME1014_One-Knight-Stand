#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "Projectile.h"

class Bullet final : public Projectile
{
public:
	Bullet(SDL_Rect s, SDL_FRect d, SDL_Texture* t, SDL_FPoint tr);
	void Update() override;
	void Render() override;
	bool m_facingLeft;
};

#endif
