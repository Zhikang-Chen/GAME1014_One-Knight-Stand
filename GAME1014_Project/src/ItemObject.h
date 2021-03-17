#pragma once
#ifndef _ITEMOBJECT_H_
#define _ITEMOBJECT_H_
#include "PlatformPlayer.h"
#include "SpriteObject.h"

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

class CheckPoint : public ItemObject
{
	
};

class HealthPotion : public ItemObject
{
	
};

#endif
