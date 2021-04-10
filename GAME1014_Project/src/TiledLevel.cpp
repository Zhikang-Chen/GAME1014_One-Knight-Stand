#include "TiledLevel.h"
#include <fstream>
#include "Slime.h"
#include "Zombie.h"

TiledLevel::TiledLevel(const unsigned short r, const unsigned short c, const int w, const int h, 
                       const char* tileData, const char* levelData, const char* tileKey) :m_rows(r), m_cols(c), m_tileKey(tileKey)
{
	xmlDoc.LoadFile(tileData);
	XMLNode* pRoot = xmlDoc.FirstChildElement("Data");
	XMLElement* pElement = pRoot->FirstChildElement("Tile");

	while(pElement != nullptr)
	{
		//It can only take one character as a key cause i don't want to deal with c string anymore
		const char* key;
		int x, y;
		//pElement->QueryStringAttribute("key", &key);

		key = pElement->Attribute("key");
		pElement->QueryAttribute("x", &x);
		pElement->QueryAttribute("y", &y);

		char k = key[0];
		if(k == 'S')
			m_tiles.emplace(k, new SpawnTile({x,y,32,32}, { 0.0f, 0.0f, (float)w, (float)h }));
		else if(k == 'E')
			m_tiles.emplace(k, new EndTile({ x,y,32,32 }, { 0.0f, 0.0f, (float)w, (float)h }));
		else if (k == 'C')
			m_tiles.emplace(k, new CheckPointTile({ x,y,32,32 }, { 0.0f, 0.0f, (float)w, (float)h }));
		else if (k == '[' || k == 'P' || k == ']')
			m_tiles.emplace(k, new Tile({ x * w, y * h, w, h }, { 0.0f, 0.0f, (float)w, (float)h }, TEMA::GetTexture(m_tileKey),PLATFORM));
		else if(k != '*' && k != 's' && k != 'z')
			m_tiles.emplace(k, new Tile({ x * w, y * h, w, h }, { 0.0f, 0.0f, (float)w, (float)h }, TEMA::GetTexture(m_tileKey), OBSTACLE));
		else
			m_tiles.emplace(k, new Tile({ x * w, y * h, w, h }, { 0.0f, 0.0f, (float)w, (float)h }, TEMA::GetTexture(m_tileKey), AIR));
		pElement = pElement->NextSiblingElement("Tile");
		
	}

	ifstream inFile(levelData);
	if (inFile.is_open())
	{
		char key;
		m_level.resize(m_rows); // Important or we cannot use subscripts.
		for (unsigned short row = 0; row < m_rows; row++)
		{
			m_level[row].resize(m_cols);
			for (unsigned short col = 0; col < m_cols; col++)
			{
				inFile >> key;
				m_level[row][col] = m_tiles[key]->Clone(); // Common prototype method.
				m_level[row][col]->SetXY((float)(col * w), (float)(row * h));
				int w, h;
				if (key == 's')
				{
					auto r = m_level[row][col]->GetDst();
					SDL_QueryTexture(TEMA::GetTexture("Slime"), nullptr, nullptr, &w, &h);
					m_enemies.push_back(new Slime({ 0,0,w,h },
						{ r->x - w, r->y - h,(float)w,(float)h }));
				}
				else if (key == 'z')
				{
					auto z = m_level[row][col]->GetDst();
					SDL_QueryTexture(TEMA::GetTexture("Zombie"), nullptr, nullptr, &w, &h);
					m_enemies.push_back(new Zombie({ 0,0,w,h },
						{ z->x - w, z->y - h,(float)w,(float)h }));
				}
				
				switch (m_level[row][col]->GetTag()) {
					case SPAWN:
						m_pStartingTile = m_level[row][col];
						m_visibleTile.push_back(m_pStartingTile);
						break;
					case CHECKPOINT:
						//m_checkPoint.push_back(m_level[row][col]);
						m_visibleTile.push_back(m_level[row][col]);
						break;
					case END:
						m_visibleTile.push_back(m_level[row][col]);
						break;
					case OBSTACLE:
						//m_obstacles.push_back(m_level[row][col]);
						m_visibleTile.push_back(m_level[row][col]);
						break;
					case PLATFORM:
						//m_checkPoint.push_back(m_level[row][col]);
						m_visibleTile.push_back(m_level[row][col]);
						break;
				}
			}
		}
	}
	inFile.close();

	 // Because of the way the program reads the txt file
	 // I have to read the vector again to get spawn and check point
	 // Fucking end me
	if(!m_level.empty())
	{
		m_checkPoint.push_back(m_pStartingTile);
		for(unsigned short col = 0; col < m_cols; col++)
		{
			for (unsigned short row = 0; row < m_rows; row++)
			{
				if(m_level[row][col]->GetTag() == CHECKPOINT)
					m_checkPoint.push_back(m_level[row][col]);
			}
		}
	}
}

TiledLevel::~TiledLevel()
{
	// Clear the tile clones. This also clears the ones in m_obstacles.
	for (unsigned short row = 0; row < m_rows; row++)
	{
		for (unsigned short col = 0; col < m_cols; col++)
		{
			delete m_level[row][col];
			m_level[row][col] = nullptr;
		}
	}
	m_level.clear();
	for (auto& enemy : m_enemies)
	{
		delete enemy;
		enemy = nullptr;
	}
	m_enemies.clear();
	for (auto& potion : m_potions)
	{
		delete potion;
		potion = nullptr;
	}
	m_potions.clear();
	m_renderTile.clear();
	m_level.clear();
	m_visibleTile.clear();
	m_enemies.clear();
	m_pStartingTile = nullptr;
	// Clear the original tiles.
	for (map<char, Tile*>::iterator i = m_tiles.begin(); i != m_tiles.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_tiles.clear();
}

void TiledLevel::Render()
{
	for (auto tile : m_renderTile)
		tile->Render();
	
	for (auto enemy : m_renderEnemies)
		enemy->Render();
	
	for (auto p : m_potions)
		p->Render();

	
}

void TiledLevel::Remove(Enemy* object)
{
	auto i = find(m_enemies.begin(), m_enemies.end(), object);
	if (i != m_enemies.end())
	{
		m_enemies.erase(i);
		m_enemies.shrink_to_fit();

		auto i2 = find(m_renderEnemies.begin(), m_renderEnemies.end(), object);
		m_renderEnemies.erase(i2);
		m_renderEnemies.shrink_to_fit();
		delete object;
	}
	else
	{
		cout << "Unable to find enemy" << endl;
	}
}

void TiledLevel::Remove(HealthPotion* object)
{
	auto i = find(m_potions.begin(), m_potions.end(), object);
	if (i != m_potions.end())
	{
		m_potions.erase(i);
		m_renderEnemies.shrink_to_fit();
		delete object;
	}
	else
	{
		cout << "Unable to find potion" << endl;
	}
}

void TiledLevel::Update()
{
	m_renderTile.clear();
	for (auto i : m_visibleTile)
	{
		if(i->GetDst()->x < WIDTH + WIDTH / 2 && i->GetDst()->x > 0 - WIDTH / 2)
		{
			m_renderTile.push_back(i);
		}
	}

	m_renderEnemies.clear();
	for(auto i : m_enemies)
	{
		if (i->GetDst()->x < WIDTH + WIDTH / 3 && i->GetDst()->x > 0 - WIDTH / 3)
		{
			i->Update();
			m_renderEnemies.push_back(i);
		}
	}
}

vector<Enemy*>& TiledLevel::GetEnemies()
{
	return m_enemies;
}

vector<Enemy*>& TiledLevel::GetRenderEnemies()
{
	return m_renderEnemies;
}

vector<Tile*>& TiledLevel::GetCheckPoint()
{
	return m_checkPoint;
}

vector<Tile*>& TiledLevel::GetVisibleTile()
{
	return m_visibleTile;
}

vector<Tile*>& TiledLevel::GetRenderTile()
{
	return m_renderTile;
}

vector<HealthPotion*>& TiledLevel::GetPotion()
{
	return m_potions;
}

Tile* TiledLevel::GetStartingTile() const
{
	return m_pStartingTile;
}

void TiledLevel::AddPotion(HealthPotion* p)
{
	m_potions.push_back(p);
}

//vector<Tile*>& TiledLevel::GetObstacles() { return m_obstacles; }

void Tile::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst);
}


void CheckPointTile::Activate()
{
	if (!m_activate)
	{
		m_activate = true;
		m_src.x = 32;
	}
}