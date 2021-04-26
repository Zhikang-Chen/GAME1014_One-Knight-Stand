#include "Bullet.h"
#include "MathManager.h"
//To Do:
// Make this work better

Bullet::Bullet(SDL_Rect s, SDL_FRect d, SDL_Texture* t, SDL_FPoint tr) : Projectile(s,d,t, tr)
{
	m_angle = MAMA::Rad2Deg(atan2(m_target.y - m_dst.y, m_target.x - m_dst.x));
}

void Bullet::Update()
{
	m_dst.x += 10 * cos(MAMA::Deg2Rad(m_angle));
	m_dst.y += 10 * sin(MAMA::Deg2Rad(m_angle));
}

void Bullet::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst, m_angle, 0, SDL_FLIP_NONE);
}
