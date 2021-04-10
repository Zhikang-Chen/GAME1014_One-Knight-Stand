#pragma once
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "States.h"
#include <vector>
#include "TiledLevel.h"
#include "Heart.h"
#include "SwordSkill.h"
#include "ItemObject.h"


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
	void MoveCamTo(GameObject* o);
	void ChangeLevel(unsigned int level);
	unsigned int GetLevel() const;
	unsigned int GetCheckPoint() const;
private:
	SwordSkill* m_pSwordSkill1;
	SwordSkill* m_pSwordSkill2;
	SwordSkill* m_pSwordSkill1CD;
	SwordSkill* m_pSwordSkill2CD;
	vector<Heart*> Hearts;

	Tile* m_spawn;
	vector<TiledLevel*> m_levels;

	// For save
	unsigned int m_currLevel;
	unsigned int m_currCheckPoint;
	
	std::vector<std::pair<std::string, GameObject*>> m_UIObject; //Almost the same as m_objecst but those wont update
};

#endif