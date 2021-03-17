#include "Slime.h"
#include "Enemy.h"

Slime::Slime(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : Enemy(s, d, t, 0, 0, 1, 1)
{
	m_health = m_maxHealth;
}

Slime::~Slime()
{

}

void Slime::Update()
{

}

void Slime::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst, m_angle, 0, m_facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Slime::AttackPattern()
{
}
