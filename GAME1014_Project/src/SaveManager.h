#pragma once
#ifndef _SAVEMANAGER_
#define _SAVEMANAGER_
#include "StateManager.h"

struct Save
{
	unsigned int m_currHealth;
	unsigned int m_maxHealth;
	unsigned int m_checkpoint;
	unsigned int m_currLevel;
};

class SaveManager
{
public:
	static void OverwriteSave();	// Overwrite data in a save struct
	static void deleteSave();		// Delete save struct
	static Save* GetSave();		// Load save struct
	
	static void load();			// Load XML file
	static void Quit();
	static void Init();
private:
	SaveManager() = default;
	static Save* m_saveDat;

	//friend GameState;
};

typedef SaveManager SAMA;

#endif
