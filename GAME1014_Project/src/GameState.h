#pragma once
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "States.h"
#include "CollisionManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include <vector>

#include "Heart.h"
#include "SwordSkill.h"

class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	void CollisionCheck();
	void UpdateCam();

private:
	Label* m_plabel;
	Label* m_weaponSkillActive;
	PlatformPlayer* m_player;
	int m_camOffset;

<<<<<<< Updated upstream
=======
	Sword* m_pWeapon;
	SwordSkill* m_pSwordSkill1;
	Heart* m_pHeartbar;
	Heart* m_pFullHeart;
	Heart* m_pEmptyHeart;

>>>>>>> Stashed changes
	vector<SDL_FRect*> m_pPlatforms;
};

#endif