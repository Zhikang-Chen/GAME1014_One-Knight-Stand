#include "Slime.h"
#include "Enemy.h"
#include "TextureManager.h"

Slime::Slime(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : Enemy(s, d, t, 0, 0, 1, 1)
{
	m_health = m_maxHealth;
}

Slime::~Slime()
{

}

void Slime::Update()
{
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), (m_grav * 4.0f)); //m_grav is how fast you're going to fall
	
}

void Slime::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("Slime"), GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
}

void Slime::AttackPattern()
{
}
