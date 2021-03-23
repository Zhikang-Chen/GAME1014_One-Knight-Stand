#include "SwordSkill.h"
#include "TextureManager.h"
SwordSkill::SwordSkill(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : SpriteObject(s, d, t) {}

void SwordSkill::Update()
{
}

void SwordSkill::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
}

Projectile::Projectile(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : SpriteObject(s, d , t)
{
	m_cooldown = 0;
}

void Projectile::Update()
{
	m_cooldown++;
	if (m_cooldown >= 200)
	{
		m_cooldown = 0;
		if (m_facing)
			m_accelX = 30.0f;
	}
	m_velX += m_accelX;
	m_dst.x += m_velX;
}
void Projectile::faceDir(bool f)
{
	m_facing = f;
}
void Projectile::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("Project"), GetSrc(), GetDst(), m_angle, 0, m_facing ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
void Projectile::SetAccelX(double a) { m_accelX = a; }

void Projectile::SetAccelY(double a) { m_accelY = a; }
float Projectile::GetVelX() { return m_velX; }

float Projectile::GetVelY() { return m_velY; }

void Projectile::SetX(float x) { this->GetDst()->x = x; }

void Projectile::SetY(float y) { this->GetDst()->y = y; }