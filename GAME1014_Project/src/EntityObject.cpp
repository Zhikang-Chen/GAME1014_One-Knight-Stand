#include "EntityObject.h"

EntityObject::EntityObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : AnimatedSpriteObject(s,d,t,0,0,0,0)
{
	m_colour = { (Uint8)225,(Uint8)225,(Uint8)225 };
}

EntityObject::~EntityObject() = default;

void EntityObject::Stop()
{
	StopX();
	StopY();
}

void EntityObject::StopX() { m_velX = 0.0; }

void EntityObject::StopY() { m_velY = 0.0; }

void EntityObject::SetAccelX(double a) { m_accelX = a; }

void EntityObject::SetAccelY(double a) { m_accelY = a; }

float EntityObject::GetVelX() { return m_velX; }

float EntityObject::GetVelY() { return m_velY; }

void EntityObject::SetX(float x) { m_dst.x = x; }

void EntityObject::SetY(float y) { m_dst.y = y; }

int EntityObject::GetHeath() { return m_curHealth; }

int EntityObject::GetMaxHealth() { return m_maxHealth; }

SDL_Color EntityObject::GetColour() { return m_colour; }

void EntityObject::SetHeath(int h) { m_curHealth = h; }

void EntityObject::SetMaxHealth(int h) { m_maxHealth = h; }

void EntityObject::faceDir(bool f) { m_facingLeft = f; }

void EntityObject::SetColour(Uint8 r, Uint8 g, Uint8 b) { m_colour = { r,g,b }; }

