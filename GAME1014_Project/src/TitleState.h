#pragma once
#ifndef _TITLESTATE_H_
#define _TITLESTATE_H_
#include "Background.h"
#include "Button.h"
#include "Label.h"
#include "States.h"
#include "Engine.h"


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