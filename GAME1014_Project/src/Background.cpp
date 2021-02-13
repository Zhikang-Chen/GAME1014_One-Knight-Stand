#include "Background.h"

Background::Background(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : SpriteObject(s, d, t) {}

void Background::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst, m_angle, 0, SDL_FLIP_NONE);
}