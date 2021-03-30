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
#include "ItemObject.h"

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
<<<<<<< Updated upstream
	Sword* m_pWeapon;
	Label* m_pSwordSkill;
	ItemObject* AnItem;
	SwordSkill* m_pSwordSkill1;
	Heart* m_pHeartbar;
	Heart* m_pFullHeart;
	Heart* m_pEmptyHeart;
=======
	SwordSkill* m_pSkillsUI;
	SwordSkill* m_pHealthUI;
	SwordSkill* m_pSwordSkill1;
	SwordSkill* m_pSwordSkill2;
	SwordSkill* m_pSwordSkill1CD;
	SwordSkill* m_pSwordSkill2CD;
	SwordSkill* m_pSwordAttack;
	vector<Heart*> Hearts;

	Tile* m_spawn;
	vector<TiledLevel*> m_levels;
	unsigned int m_currLevel;
	
>>>>>>> Stashed changes
	std::vector<std::pair<std::string, GameObject*>> m_UIObject; //Almost the same as m_objecst but those wont move with the camera
};

#endif