#include "Zombie.h"
#include "Enemy.h"
#include "TextureManager.h"

Zombie::Zombie(SDL_Rect s, SDL_FRect d) : Enemy(s, d, TEMA::GetTexture("Zombie"))
{
	m_maxHealth = 7;
	m_curHealth = 7;
}

void Zombie::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrc(), GetDst(), m_angle, 0, m_facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Zombie::Move()
{
		//The zombie will slowly approach the player.
		if (m_facingLeft)
			m_accelX = 0.2f;
			
		else
			m_accelX = -0.2f;
}
