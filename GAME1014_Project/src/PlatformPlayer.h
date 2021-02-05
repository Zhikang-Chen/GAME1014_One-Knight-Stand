#pragma once
#ifndef _PLATFORMPLAYER_H_
#define _PLATFORMPLAYER_H_
#define GRAV 6.0 //Gravity
#define JUMPFORCE 60.0; //Acceleration
#include "SpriteObject.h"
#include "TextureManager.h"
#include "MathManager.h"

enum PlayerState {STATE_IDLING, STATE_RUNNING, STATE_JUMPING};

class PlatformPlayer : public AnimatedSpriteObject
{
public:
	PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Texture* t);

	//PlatformPlayer(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t)
	//	:SpriteObject(s, { static_cast<float>(d.x, d.y, d.w, d.h)}, r, t) {}
	
	void Init();
	void Update();
	void Render();

	void ShowHitbox();
	
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

private:
	// Private member
	bool m_grounded; //In most platforming games, the player actually starts in the air
	bool m_alive; //Game runs while player is alive, shows black screen when dead.
	bool m_facingLeft;
	bool m_showHitbox;
	PlayerState m_state;
	double m_accelX, //Acceleration on the X axis, horizontal force
		m_accelY,//Acceleration on the Y axis, vertical force
		m_velX, //Velocity for X 
		m_maxVelX, //Maximum velocity
		m_velY, //Velocity for Y
		m_maxVelY,
		m_drag,
		m_grav;
	//SDL_Rect m_rect;

	


	
};

#endif
