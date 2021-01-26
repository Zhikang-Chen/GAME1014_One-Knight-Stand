#pragma once
#ifndef _TITLESTATE_H_
#define _TITLESTATE_H_
#include "States.h"


class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

#endif
