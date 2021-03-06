#include "WeaponObject.h"

#include "MathManager.h"

Sword::Sword(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : WeaponObject(s, d, t) {}

void Sword::Update()
{
	GetDst()->x = m_pTarget->x + m_pTarget->w / 1.5;
	GetDst()->y = m_pTarget->y;
}


void Sword::SetTarget(SDL_FRect* d)
{
	m_pTarget = d;
}
