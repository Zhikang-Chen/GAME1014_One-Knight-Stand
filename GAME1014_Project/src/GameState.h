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

#include "TiledLevel.h"
#include "Heart.h"
#include "SwordSkill.h"
#include "Slime.h"

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
	void UpdateCam(GameObject* o);
	void ChangeLevel(unsigned int level);

private:
	SwordSkill* m_pSwordSkill1;
	SwordSkill* m_pSwordAttack;
	vector<Heart*> Hearts;

	Tile* m_spawn;
	vector<TiledLevel*> m_levels;
	unsigned int m_currLevel;
	
	std::vector<std::pair<std::string, GameObject*>> m_UIObject; //Almost the same as m_objecst but those wont move with the camera
};

#endif