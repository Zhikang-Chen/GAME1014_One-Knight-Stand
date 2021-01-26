#pragma once
#ifndef _STATES_H_
#define _STATES_H_

class State // This is the abstract base class for all states
{
public:
	virtual void Enter() = 0; // = 0 means pure virtual - must be defined in subclass
	virtual void Update() = 0; 
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume(); 
	virtual ~State() = default; // Modern alternative to {}
protected: // Private but inherited
	State() {}; // What does this prevent?
};



#endif

