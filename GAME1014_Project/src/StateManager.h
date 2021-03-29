#pragma once
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "TitleState.h"
#include "GameState.h"
#include "States.h"
#include <vector>


class StateManager
{
public:// Public methods.
	static void Update();
	static void Render();
	static void PushState(State* pState);
	static void ChangeState(State* pState);
	static void PopState();
	static void Quit();
	static std::vector<State*>& GetStates();
private: // Private methods.
	static std::vector<State*> s_states;
	static State* m_pNextState;
	StateManager() {}
	
};

typedef StateManager STMA;

#endif

