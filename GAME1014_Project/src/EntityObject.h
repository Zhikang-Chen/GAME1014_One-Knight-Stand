#pragma once
#ifndef _ENTITYOBJECT_
#define _ENTITYOBJECT_
#define GRAV 4.0 //Gravity
#define JUMPFORCE 40.0; //Acceleration
#include "SpriteObject.h"
#include <algorithm>

class EntityObject : public AnimatedSpriteObject
{
public:
	EntityObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	virtual ~EntityObject();
	
	// Stop movement
	virtual void Stop();
	virtual void StopX();
	virtual void StopY();

	// Setter
	virtual void SetAccelX(double a);
	virtual void SetAccelY(double a);
	virtual void SetX(float x);
	virtual void SetY(float y);
	virtual void SetHeath(int h);
	virtual void SetMaxHealth(int h);
	virtual void faceDir(bool f);
	virtual void SetColour(Uint8 r, Uint8 g, Uint8 b);

	// Getter
	virtual float GetVelX();
	virtual float GetVelY();
	virtual int GetHeath();
	virtual int GetMaxHealth();
	virtual SDL_Color GetColour();

protected:
	virtual void Update() = 0;
	virtual void Render() = 0;
	// Private member
	bool m_facingLeft;

	float m_accelX, //Acceleration on the X axis, horizontal force
		m_accelY,//Acceleration on the Y axis, vertical force
		m_velX, //Velocity for X 
		m_maxVelX, //Maximum velocity
		m_velY, //Velocity for Y
		m_maxVelY,
		m_drag,
		m_grav;
	int m_curHealth,
		m_maxHealth;

	SDL_Color m_colour;
};

#endif
