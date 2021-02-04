#pragma once
#ifndef _TITLESTATE_H_
#define _TITLESTATE_H_
#include "Label.h"
#include "States.h"

#include "PlatformPlayer.h"
#include "CollisionManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "StateManager.h"
#include "TextureManager.h"

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	void CollisionCheck();
	void UpdateCam();

private:
	Label* m_pTitle;
	Label *m_pSubTitle;
	Label* something;
	Sprite* m_pBackground;

};

#endif