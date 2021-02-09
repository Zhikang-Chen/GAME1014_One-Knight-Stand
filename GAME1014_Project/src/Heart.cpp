#include "Heart.h"

Heart::Heart(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : SpriteObject(s, d, t) {}

void Heart::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrcP(), GetDstP(), m_angle, 0, SDL_FLIP_NONE);
}