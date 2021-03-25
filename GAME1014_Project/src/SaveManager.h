#pragma once
#ifndef _SAVEMANAGER_
#define _SAVEMANAGER_
#include <vector>

struct Save
{
	int m_currHealth;
	int m_maxHealth;
	int m_checkpoint;
	int m_currLevel;
};

class SaveManager
{
public:
	
	static void createSave();		// Create a save struct
	static void OverwriteSave();	// Overwrite data in a save struct
	static void deleteSave();		// Delete save struct
	static void loadSave();		// Load save struct
	
	static void load();			// Load XML file
	static void Quit();
	static void Init();
private:
	SaveManager() = default;
	static std::vector<Save*> m_saveDat;
};

typedef SaveManager SAMA;

#endif
