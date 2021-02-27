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
	Sword* m_pWeapon;
	ItemObject* AnItem;
	std::vector<std::pair<std::string, GameObject*>> m_UIObject; //Almost the same as m_objecst but those wont move with the camera
};

#endif