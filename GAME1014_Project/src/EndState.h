#pragma once
#ifndef _ENDSTATE_H_
#define _ENDSTATE_H_
#include "States.h"

class EndState : public State
{
public:
	EndState(){};
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
private:
	
};

#endif
