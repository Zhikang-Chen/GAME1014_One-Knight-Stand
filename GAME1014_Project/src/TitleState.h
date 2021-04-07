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

private:
	Label* m_pTitle;
	Label *m_pSubTitle;
	Label* m_pInstruction;

	Background* bleh;
	Button* b;
	ExitButton* e;
	Background* m_pBackground;
	Mix_Music* m_titleBgm;

};

#endif