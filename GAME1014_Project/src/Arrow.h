#pragma once
#ifndef _ARROW_
#define _ARROW_
#include "Projectile.h"

class Arrow final : public Projectile
{
public:
	Arrow(SDL_Rect s, SDL_FRect d, SDL_Texture* t, SDL_FPoint tr);
	void Update() override;
	void Render() override;
private:
	int m_flyTime;
	float Vox;
	float Voy;
};

#endif
