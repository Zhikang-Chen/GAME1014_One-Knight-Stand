#pragma once
#ifndef _TITLESTATE_H_
#define _TITLESTATE_H_
#include "Label.h"
#include "States.h"

#include "PlatformPlayer.h"

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	void CollisionCheck();

private:
	Label *m_plabel;
	PlatformPlayer *fml;

	SDL_FRect *m_platforms;
};

#endif