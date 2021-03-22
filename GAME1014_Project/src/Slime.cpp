#include "Slime.h"
#include "Enemy.h"
#include "TextureManager.h"

Slime::Slime(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : Enemy(s, d, t, 0, 0, 1, 1)
{
	m_maxHealth = m_health = 1;
	m_jumpTimer = 0;
}

void Slime::Update()
{
	
	//m_accelY = -JUMPFORCE;
	// x axis
	m_velX += m_accelX;
	m_velX *= (m_grounded ? m_drag : 1.0f);

	//Velocity clamping
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX); //std::max first check, std::min second	
	m_dst.x += m_velX;

	// y axis
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), (m_grav * 4.0f)); //m_grav is how fast you're going to fall
	m_dst.y += m_velY;

	//Reset acceleration
	m_accelX = m_accelY = 0.0; //Similar to a keyup event
	AttackPattern();
}

void Slime::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("Slime"), GetSrc(), GetDst(), m_angle, 0, m_facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Slime::faceDir(bool f)
{
	m_facingLeft = f;
}


void Slime::AttackPattern()
{
	m_jumpTimer++;
	if (m_jumpTimer >= 40)
	{
		m_jumpTimer = 0;
		if (m_facingLeft)
			m_accelX = 30.0f;
		else
			m_accelX = -30.0f;
		m_accelY = -JUMPFORCE; // SetAccelY(-JUMPFORCE);
	}
}
