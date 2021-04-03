#include "Slime.h"
#include "Enemy.h"
#include "TextureManager.h"

Slime::Slime(SDL_Rect s, SDL_FRect d) : Enemy(s, d, TEMA::GetTexture("Slime"))
{
	m_maxHealth = m_curHealth = 5;
	m_jumpTimer = 0;
}

void Slime::Move()
{
	m_jumpTimer++;
	if(m_jumpTimer >= 120)
	{
		m_jumpTimer = 0;
		if(m_facingLeft)
			m_accelX = 30.0f;
		else
			m_accelX = -30.0f;
		m_accelY = -JUMPFORCE; // SetAccelY(-JUMPFORCE);
	}

	//m_accelY = JUMPFORCE;
}
