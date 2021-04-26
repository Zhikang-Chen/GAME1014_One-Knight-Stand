#include "Projectile.h"

Projectile::Projectile(SDL_Rect s, SDL_FRect d, SDL_Texture* t, SDL_FPoint tr)
: AnimatedSpriteObject(s,d,t,0,0,0,0), m_target(tr) {}

const SDL_FPoint Projectile::GetTarget()
{
	return m_target;
}

void Projectile::SetTarget(SDL_FPoint t)
{
	m_target = t;
}

void Projectile::SetTarget(float x, float y)
{
	m_target = { x, y };
}
