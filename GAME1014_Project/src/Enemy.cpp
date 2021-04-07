#include "Enemy.h"

Enemy::Enemy(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : EntityObject(s, d, t),
m_grounded(false)
{
	m_maxVelX = 10.0;
	m_maxVelY = 40.0;
	m_grav = GRAV;
	m_drag = 0.85;
	m_facingLeft = false;
	
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	m_maxHealth = m_curHealth = INFINITY;

}

Enemy::~Enemy()
{
	for(auto &e : m_effects)
	{
		delete e;
		e = nullptr;
	}
	m_effects.clear();
}

// I don't like update to be change so don't
// If you want to change anything do it with Move
void Enemy::Update()
{
	if (m_dst.x < WIDTH + WIDTH / 2 && m_dst.x > 0 - WIDTH / 2)
	{
		m_inRenderRange = true;
		Move();
		for (unsigned int i = 0; i < m_effects.size(); i++)
		{
			m_effects[i]->Update();
			if (m_effects[i]->HasEffectEnd())
			{
				delete m_effects[i];
				m_effects.erase(m_effects.begin() + i);
				m_effects.shrink_to_fit();
			}
		}

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
	}
	else
		m_inRenderRange = false;
}

void Enemy::Render()
{
	if (m_inRenderRange)
	{
		SDL_SetTextureColorMod(m_pText, m_colour.r, m_colour.g, m_colour.b);
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrc(), GetDst(), m_angle, 0, m_facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		SDL_SetTextureColorMod(m_pText, 225, 225, 225);
	}
}

void Enemy::LoseHealth() { m_curHealth -= 1; } //Send the player's weapon damage in as argument

bool Enemy::IsGrounded() { return m_grounded; }

bool Enemy::SetGrounded(bool g) { return m_grounded = g; }

void Enemy::addEffect(Effect* e)
{
	for (auto ef : m_effects)
	{
		if(ef->GetType() == e->GetType())
		{
			delete e;
			return;
		}
	}
	e->SetEffectedEntity(this);
	m_effects.push_back(e);
}

