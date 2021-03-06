#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "SpriteObject.h"

class WeaponObject : public SpriteObject
{
protected:
	//int m_Damage;
	//string m_Name;
	//string m_Des;
	
public:
	WeaponObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t)
		: SpriteObject(s, d, t) {}

	
};

//To do refactor them

class Sword : public WeaponObject
{
private:
	//PlatformPlayer	* m_player;
	SDL_FRect* m_pTarget;
	
	void Update() override;
	
public:
	void SetTarget(SDL_FRect* d);
	Sword(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
};

#endif
