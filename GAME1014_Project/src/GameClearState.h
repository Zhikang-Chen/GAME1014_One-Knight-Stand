#pragma once
#ifndef _GAMECLEARSTATE_H_
#define _GAMECLEARSTATE_H_
#include "States.h"
#include "Background.h"
#include "Button.h"
#include "Label.h"
#include "States.h"

class GameClearState : public State
{
public:
	GameClearState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	

private:
	Background* m_gClearBackground;
};

#endif