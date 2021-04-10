#pragma once
#ifndef _ITEMOBJECT_H_
#define _ITEMOBJECT_H_
#include "PlatformPlayer.h"
#include "SpriteObject.h"
#include "TextureManager.h"

class ItemObject : public SpriteObject
{
public:
	ItemObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : SpriteObject(s,d,t), m_Activate(false){}

	void Update() override;
	void Activate(PlatformPlayer* p) { m_Activate = true; }

private:
	string m_name;
	bool m_Activate;
	virtual void DoesStuff() { cout << "Doing stuff" << endl; };
};

class HealthPotion : public ItemObject
{
public:
	HealthPotion(SDL_Rect s, SDL_FRect d) : ItemObject(s, d, TEMA::GetTexture("Potion")){}

	void Render()
	{
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("Potion"), GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
	}
};

#endif
