﻿#pragma once
#ifndef _PLATFORMPLAYER_H_
#define _PLATFORMPLAYER_H_
#include "EntityObject.h"
#include "Projectile.h"

enum class PlayerState {STATE_IDLING, STATE_RUNNING, STATE_JUMPING, STATE_ATTACKING};

enum class AttackType {NONE,NORMAL, ICE, BONK, BLEED};

class PlatformPlayer : public EntityObject
{
public:
	PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	~PlatformPlayer();
	//PlatformPlayer(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t)
	//	:SpriteObject(s, { static_cast<float>(d.x, d.y, d.w, d.h)}, r, t) {}

	void Update();
	void Render();

	void ShowHitbox();
	void Remove(Projectile* object);

	PlayerState GetState();

	bool IsGrounded();
	bool SetGrounded(bool g);

	// GetDst and GetBoundingBox now both return m_pBoundingBox
	// Too much work to remove GetBoundingBox so it will stay
	SDL_FRect* GetDst() { return &m_pBoundingBox; }
	//SDL_FRect* GetBoundingBox();
	SDL_FRect* GetAttackHitBox();
	AttackType GetCurrentAttack() const;

	vector<Projectile*>& GetProjectiles();
	
	bool getSkill1CD() { return m_isSkillUp; }
	bool setSkill1CD(bool setSkillCD)
	{
		m_isSkillUp = setSkillCD;
		return m_isSkillUp;
	}
	bool getSkill2CD() { return m_isSkillUpSTUN; }
	bool setSkill2CD(bool setSkillCD)
	{
		m_isSkillUpSTUN = setSkillCD;
		return m_isSkillUpSTUN;
	}
	void SetX(float x);
	void SetY(float y);

private:
	// Private member
	SDL_FRect m_pBoundingBox;
	SDL_FRect m_pAttackHitBox;

	vector<Projectile*> m_projectile;

	bool m_grounded; //In most platforming games, the player actually starts in the air
	bool m_showHitbox;
	PlayerState m_state;

	AttackType m_currentAttack;
	bool m_isSkillUp;
	int skillTimer = 0;

	bool m_isSkillUpSTUN;
	int skillSTUNTimer = 0;

};
#endif
