#pragma once
#ifndef _PLATFORMPLAYER_H_
#define _PLATFORMPLAYER_H_
#define GRAV 4.0f //Gravity
#define JUMPFORCE 40.0f //Acceleration
#define DRAG 0.85 //Acceleration
#include "EntityObject.h"

enum PlayerState {STATE_IDLING, STATE_RUNNING, STATE_JUMPING, STATE_ATTACKING, STATE_SPECIAL_ATTACK};

class PlatformPlayer : public EntityObject
{
public:
	PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Texture* t);

	//PlatformPlayer(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t)
	//	:SpriteObject(s, { static_cast<float>(d.x, d.y, d.w, d.h)}, r, t) {}

	void Update();
	void Render();

	void ShowHitbox();
	
	PlayerState GetState();

	bool IsGrounded();
	bool SetGrounded(bool g);

	// GetDst and GetBoundingBox now both return m_pBoundingBox
	// Too much work to remove GetBoundingBox so it will stay
	SDL_FRect* GetDst() { return &m_pBoundingBox; }
	//SDL_FRect* GetBoundingBox();
	SDL_FRect* GetAttackHitBox();

	void SetX(float x);
	void SetY(float y);

private:
	// Private member
	SDL_FRect m_pBoundingBox;
	SDL_FRect m_pAttackHitBox;
	bool m_grounded; //In most platforming games, the player actually starts in the air
	bool m_showHitbox;
	PlayerState m_state;
};

#endif
