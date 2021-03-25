#include "SaveManager.h"

#include <iostream>

#include "tinyxml2.h"
#include "string"

void SaveManager::createSave()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../Dat/SaveData.xml");
	tinyxml2::XMLNode* pRoot = doc.FirstChildElement("Root");

	
}

void SaveManager::OverwriteSave()
{
}

void SaveManager::deleteSave()
{
}

void SaveManager::loadSave()
{
}

void SaveManager::load()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../GAME1017_Template_W01/Dat/SaveData.xml");
	tinyxml2::XMLNode* pRoot = doc.FirstChildElement("Root");

	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement("Save");
	int x;
	pElement->QueryAttribute("Slot", &x);
	std::cout << x << std::endl;

}

void SaveManager::Quit()
{
}

void SaveManager::Init()
{
	load();
}

std::vector<Save*> m_saveDat;