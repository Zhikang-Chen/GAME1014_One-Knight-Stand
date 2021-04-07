#pragma once
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "TitleState.h"
#include "GameState.h"
#include "PauseState.h"
#include "LoadState.h"
#include "EndState.h"

#include "States.h"


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
	static bool m_popBackState;
	StateManager() {}
	
};

typedef StateManager STMA;

#endif

