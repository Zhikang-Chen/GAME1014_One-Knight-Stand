#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define GRAV 4.0
#define JUMPFORCE 40.0; //Acceleration
#include "EntityObject.h"
#include "Effect.h"

class Enemy : public EntityObject
{
public:
	Enemy(SDL_Rect s, SDL_FRect, SDL_Texture* t);
	virtual ~Enemy();
	
	virtual void Update();
	virtual void Render();
	
	virtual void LoseHealth();
	virtual void Move(){}

	virtual bool DropTable(int r) { return false; }

	bool IsGrounded();
	bool SetGrounded(bool g);

	void addEffect(Effect* e);

protected:
	bool m_grounded;
	vector<Effect*> m_effects;
	
	friend Effect;
};


#endif