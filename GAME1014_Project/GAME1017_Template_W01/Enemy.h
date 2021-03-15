#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define GRAV 4.0

#include "SpriteObject.h"

class Enemy : public AnimatedSpriteObject
{
private:
protected:
	/*A lot of this stuff is copied over from the PlatformPlayer class,
	* but I don't think it makes sense to make Enemy a child of PlatformPlayer so here we are*/
	bool m_grounded;
	bool m_facingLeft = false;
	bool m_alive;
	int m_health;
	double m_accelX, //Acceleration on the X axis, horizontal force
		m_accelY,//Acceleration on the Y axis, vertical force
		m_velX, //Velocity for X 
		m_maxVelX, //Maximum velocity
		m_velY, //Velocity for Y
		m_maxVelY,
		m_drag,
		m_grav;

public:
	Enemy(SDL_Rect s, SDL_FRect d, SDL_Texture* t, int sstart, int smin, int smax, int nf);
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(double a);
	void SetAccelY(double a);
	bool IsGrounded();
	bool SetGrounded(bool g);
	bool GetAlive();
	void SetAlive(bool a);
	double GetVelX();
	double GetVelY();
	void SetX(float x);
	void SetY(float y);
	void Update();
	void Render();
	void LoseHealth();

};


#endif