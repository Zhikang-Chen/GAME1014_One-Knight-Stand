#include "SaveManager.h"
#include "tinyxml2.h"

void SaveManager::OverwriteSave()
{
	auto s = dynamic_cast<GameState*>(STMA::GetStates().back());
	for (auto s : STMA::GetStates())
	{
		auto GS = dynamic_cast<GameState*>(s);
		if (GS != nullptr)
		{
			tinyxml2::XMLDocument doc;
			doc.LoadFile("../GAME1017_Template_W01/Dat/SaveData.xml");
			tinyxml2::XMLElement* pRoot = doc.FirstChildElement("Root");
			tinyxml2::XMLElement* pPlayer = pRoot->FirstChildElement("Save")->FirstChildElement("Player");

			if (pPlayer != nullptr)
			{
				auto p = dynamic_cast<PlatformPlayer*>(s->FindObject("Player"));

				pPlayer->SetAttribute("Health", p->GetHeath());
				pPlayer->SetAttribute("MaxHeath", p->GetMaxHealth());
				pPlayer->SetAttribute("Checkpoint", GS->GetCheckPoint());
				pPlayer->SetAttribute("Level", GS->GetLevel());
				doc.SaveFile("../GAME1017_Template_W01/Dat/SaveData.xml");
				cout << "Data Save" << endl;
				break;
			}
			else
			{
				cout << "Error: Could Not Load SaveDat" << endl;
			}
		}
	}
}

void SaveManager::resetSave()
{
		tinyxml2::XMLDocument doc;
		doc.LoadFile("../GAME1017_Template_W01/Dat/SaveData.xml");
		tinyxml2::XMLElement* pRoot = doc.FirstChildElement("Root");
		tinyxml2::XMLElement* pPlayer = pRoot->FirstChildElement("Save")->FirstChildElement("Player");

		if (pPlayer != nullptr)
		{
			pPlayer->SetAttribute("Health", 10);
			pPlayer->SetAttribute("MaxHeath", 10);
			pPlayer->SetAttribute("Checkpoint", 0);
			pPlayer->SetAttribute("Level", 0);
			doc.SaveFile("../GAME1017_Template_W01/Dat/SaveData.xml");
			cout << "Data Rest" << endl;
		}
		else
		{
			cout << "Error: Could Not Load SaveDat" << endl;
		}
}

SaveManager::Save* SaveManager::GetSave()
{
	return m_saveDat;
}

void SaveManager::load()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../GAME1017_Template_W01/Dat/SaveData.xml");
	tinyxml2::XMLNode* pRoot = doc.FirstChildElement("Root");

	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement("Save");
	//pElement->QueryAttribute("Slot", &x);

	tinyxml2::XMLElement* pSubElement = pElement->FirstChildElement("Player");
	
	int v;
	m_saveDat = new Save;
	
	pSubElement->QueryAttribute("Health", &v);
	m_saveDat->m_currHealth = v;
	
	pSubElement->QueryAttribute("MaxHeath", &v);
	m_saveDat->m_maxHealth = v;
	
	pSubElement->QueryAttribute("Checkpoint", &v);
	m_saveDat->m_checkpoint = v;
	
	pSubElement->QueryAttribute("Level", &v);
	m_saveDat->m_currLevel = v;

	//m_saveDat.push_back(temp);
	//temp = nullptr;
}

void SaveManager::Quit()
{
	delete m_saveDat;
	m_saveDat = nullptr;
}

void SaveManager::Init()
{
	load();
}

SaveManager::Save* SaveManager::m_saveDat;