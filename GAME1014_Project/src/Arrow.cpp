#include "Arrow.h"
#include "MathManager.h"

Arrow::Arrow(SDL_Rect s, SDL_FRect d, SDL_Texture* t, SDL_FPoint tr) : Projectile(s,d,t, tr)
{
	auto Rad = atan2(m_target.y - m_dst.y, m_target.x - m_dst.x);
	m_flyTime = 0;
	Vox = 12 * cos(Rad);
	Voy = 12 * sin(Rad);

	m_angle = MAMA::Rad2Deg(Rad);
}

void Arrow::Update()
{
	m_dst.x += Vox;
	m_dst.y += Voy;
	
	m_flyTime++;
	Voy += 0.3 * m_flyTime / 60;
	
	SetAngle(MAMA::Rad2Deg(atan2(Voy , Vox)));
	
}

void Arrow::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst, m_angle, 0, SDL_FLIP_NONE);
}
