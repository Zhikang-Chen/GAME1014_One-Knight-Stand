#pragma once
#ifndef _PLATFORMPLAYER_H_
#define _PLATFORMPLAYER_H_
#define GRAV 6.0 //Gravity
#define JUMPFORCE 60.0; //Acceleration
#include "SDL.h"

class PlatformPlayer
{
private:
	bool m_grounded; //In most platforming games, the player actually starts in the air
	double m_accelX, //Acceleration on the X axis, horizontal force
		m_accelY,//Acceleration on the Y axis, vertical force
		m_velX, //Velocity for X 
		m_maxVelX, //Maximum velocity
		m_velY, //Velocity for Y
		m_maxVelY,
		m_drag,
		m_grav;
	SDL_Rect m_rect;
	SDL_Renderer* m_rend;

public:
	void Init(SDL_Renderer* r);//PlatformPlayer(SDL_Renderer* r);
	SDL_Rect GetRect();
	void Update();
	void Render();
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(double a);
	void SetAccelY(double a);
	bool IsGrounded();
	bool SetGrounded(bool g);
	double GetVelX();
	double GetVelY();
	void SetX(float x);
	void SetY(float y);
	
	
	
	
};

#endif
