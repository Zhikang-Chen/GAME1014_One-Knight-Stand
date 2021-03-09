#include "Heart.h"
#include "TextureManager.h"

Heart::Heart(SDL_Rect s, SDL_FRect d) : SpriteObject(s, d, TEMA::GetTexture("HeartBar")), m_empty(false){ }

void Heart::SetEmpty(bool e)
{
	m_empty = e;
}

bool Heart::GetEmpty()
{
	return m_empty;
}

void Heart::Render()
{
	if (!m_empty)
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
	else
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("EmptyHeart"), GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
}
