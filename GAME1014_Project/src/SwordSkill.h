#pragma once
#ifndef _SWORDSKILL_H_
#define _SWORDSKILL_H_
#include "SpriteObject.h"

class SwordSkill : public SpriteObject
{
public:
	SwordSkill(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	void Update() ;
	void Render();
};

class Projectile : public SpriteObject
{
private:
	bool m_cooldown;
	bool m_facing = false;
	SDL_FRect m_pBoundingBox;
	float m_accelX, //Acceleration on the X axis, horizontal force
		m_accelY,//Acceleration on the Y axis, vertical force
		m_velX, //Velocity for X 
		m_maxVelX, //Maximum velocity
		m_velY, //Velocity for Y
		m_maxVelY;
public:
	Projectile(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	void Update();
	void Render();
	void faceDir(bool f);
	float GetVelX();
	float GetVelY();
	void SetX(float x);
	void SetY(float y);
	void SetAccelX(double a);
	void SetAccelY(double a);
	SDL_FRect* GetDst() { return &m_pBoundingBox; }
};

#endif

