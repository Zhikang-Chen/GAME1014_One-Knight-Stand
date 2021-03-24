#include "SwordSkill.h"

SwordSkill::SwordSkill(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : SpriteObject(s, d, t) {}

void SwordSkill::Update()
{
}

void SwordSkill::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
}