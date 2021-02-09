#include "WeaponObject.h"

#include "MathManager.h"

Sword::Sword(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : WeaponObject(s, d, t) {}

void Sword::Update()
{
	GetDstP()->x = m_pTarget->x + m_pTarget->w / 1.5;
	GetDstP()->y = m_pTarget->y;
}

void Sword::Render()
{
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &MAMA::ConvertFRect2Rect(m_dst));
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrcP(), GetDstP(), m_angle, 0, SDL_FLIP_NONE);
}

void Sword::SetTarget(SDL_FRect* d)
{
	m_pTarget = d;
}
