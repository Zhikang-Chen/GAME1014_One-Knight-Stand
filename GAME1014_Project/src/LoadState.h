#pragma once
#ifndef _LOADSTATE_H_
#define _LOADSTATE_H_

#include "SpriteObject.h"
#include "States.h"

class LoadState : public State
{
public:
	LoadState() {};
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
private:
	int m_frame;
	int m_endFrame;
	//Label* m_load;
	//Label* m_loadText;
	SpriteObject* LoadSword;
};

#endif