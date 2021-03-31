#include "Zombie.h"
#include "Enemy.h"
#include "TextureManager.h"

Zombie::Zombie(SDL_Rect s, SDL_FRect d) : Enemy(s, d, TEMA::GetTexture("Zombie"))
{
	m_maxHealth = 7;
	m_curHealth = 7;
}

void Zombie::Update()
{

	Move();
	m_velX += m_accelX;
	m_velX *= (m_grounded ? m_drag : 1.0f);

	//Velocity clamping
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX);
	m_dst.x += m_velX;

	// y axis
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), (m_grav * 4.0f)); 
	m_dst.y += m_velY;

	
	m_accelX = m_accelY = 0.0; 
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
