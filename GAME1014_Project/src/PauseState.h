#pragma once
#ifndef _PAUSESTATE_H_
#define _PAUSESTATE_H_
#include "Button.h"
#include "States.h"


class PauseState : public State
{
public:
	PauseState();

private:
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	BoolButton* m_pbutton;
	BoolButton* m_pbutton2;
	//SpriteObject* m_pBackground;
	
};

#endif
