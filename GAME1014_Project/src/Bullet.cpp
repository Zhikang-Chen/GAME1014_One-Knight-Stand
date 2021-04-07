#include "Bullet.h"

#include "TextureManager.h"

Bullet::Bullet(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : EntityObject(s, d, TEMA::GetTexture("Project"))
{
	m_maxVelX = 10.0;


}

void Bullet::Update()
{
	m_dst.x += 1.5;
}


void Bullet::Render()

{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
}