#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define GRAV 4.0
#define JUMPFORCE 40.0; //Acceleration
#include "EntityObject.h"

class Enemy : public EntityObject
{
public:
	Enemy(SDL_Rect s, SDL_FRect d, SDL_Texture* t);

	virtual void Update();
	virtual void Render();
	
	virtual void LoseHealth();
	virtual void AttackPattern(){};

	bool IsGrounded();
	bool SetGrounded(bool g);

protected:
	/*A lot of this stuff is copied over from the PlatformPlayer class,
	* but I don't think it makes sense to make Enemy a child of PlatformPlayer so here we are*/
	bool m_grounded;
	bool m_alive;

};


#endif