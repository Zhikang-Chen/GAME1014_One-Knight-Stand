#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include <map>
#include <SDL.h>
#include <string>
#include <vector>
#include <algorithm> 

#include "GameObject.h"

class State // This is the abstract base class for all specific states.
{
public: // Public methods.
	virtual void Update() = 0; // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Enter() = 0;  // Virtual keyword means we can override in derived class.
	virtual void Exit() = 0;
	virtual void Resume();
	// A temporary solution. waiting for Alex to teach us how to deal with pair
	GameObject* FindObject(std::string id);

protected: // Private but inherited.
	State() {}
	//std::map<std::string, GameObject*> m_objects;
	std::vector<std::pair<std::string, GameObject*>> m_objects;
};

#endif