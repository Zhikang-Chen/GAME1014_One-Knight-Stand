#pragma once
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

//┬──┬ ノ(゜ - ゜ノ) on Urban Dictionary
//He is conflicted to flip the table.
//He stares endlessly into the table's polished wood.
//He gazes upon the earth in wonderment.
//He throws caution to the wind and grabs it by its side. But then he stops.
//He looks at the floor surrounding him.
//"Someone stayed and worked on this table for hours on end, and my rage should be its undoing?"
//His thoughts drown him as he continues to stare at the table
//
//is ┬──┬ ノ(゜ - ゜ノ) home ?

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
	vector<Heart*> Hearts;
	vector<Slime*> m_slimes;

	Tile* m_spawn;
	vector<TiledLevel*> m_levels;
	unsigned int m_currLevel;
	
	std::vector<std::pair<std::string, GameObject*>> m_UIObject; //Almost the same as m_object but those wont move with the camera
};

#endif