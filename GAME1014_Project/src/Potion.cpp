#include "Potion.h"
#include "SpriteObject.h"
#include "TextureManager.h"

Potion::Potion(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : AnimatedSpriteObject(s, d, t, 0, 0, 1, 1)
{

}

void Potion::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("Potion"), GetSrc(), GetDst(), m_angle, 0, m_facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}