#include "TiledLevel.h"

TiledLevel::TiledLevel(const unsigned short r, const unsigned short c, const int w, const int h, 
	const char* tileData, const char* levelData, const char* tileKey) :m_rows(r), m_cols(c), m_tileKey(tileKey)
{
	//ifstream inFile(tileData);	
	//if (inFile.is_open())
	//{
	//	char key;
	//	int x, y;
	//	bool obs, haz;
	//	while (!inFile.eof())
	//	{
	//		inFile >> key >> x >> y >> obs >> haz;
	//		if(key != '*')
	//			m_tiles.emplace(key, new Tile({ x * w, y * h, w, h }, { 0.0f, 0.0f, (float)w, (float)h }, TEMA::GetTexture(m_tileKey) ,obs, haz));
	//		else
	//			m_tiles.emplace(key, new Tile({ x * w, y * h, w, h }, { 0.0f, 0.0f, (float)w, (float)h }, TEMA::GetTexture(m_tileKey), obs, haz, AIR));

	//	}
	//}
	//inFile.close();

	xmlDoc.LoadFile(tileData);
	XMLNode* pRoot = xmlDoc.FirstChildElement("Data");
	XMLElement* pElement = pRoot->FirstChildElement("Tile");

	while(pElement != nullptr)
	{
		//It can only take one character as a key cause i don't want to deal with c string anymore
		const char* key;
		int x, y, obs, haz;
		//pElement->QueryStringAttribute("key", &key);

		key = pElement->Attribute("key");
		pElement->QueryAttribute("x", &x);
		pElement->QueryAttribute("y", &y);
		pElement->QueryAttribute("obs", &obs);
		pElement->QueryAttribute("haz", &haz);
		
		char k = key[0];
		if(k == 'S')
			m_tiles.emplace(k, new SpawnTile({0,0,32,32}, { 0.0f, 0.0f, (float)w, (float)h }));
		else if(k == 'E')
			m_tiles.emplace(k, new EndTile({ 0,0,32,32 }, { 0.0f, 0.0f, (float)w, (float)h }));
		else if(k != '*')
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
				
				//if (m_level[row][col]->GetTag() == OBSTACLE)
				//	m_obstacles.push_back(m_level[row][col]);

				//if (key == 'S')
				//	m_pStartingTile = m_level[row][col];

				//if(key == 'E')
				//	m_pEndTile = m_level[row][col];

				//if (key == 'C')
				//	m_checkPoint.push_back(m_level[row][col]);

				switch (m_level[row][col]->GetTag()) {
					case SPAWN:
						m_pStartingTile = m_level[row][col];
						m_visibleTile.push_back(m_pStartingTile);
						break;
					case END:
						m_pEndTile = m_level[row][col];
						m_visibleTile.push_back(m_pEndTile);
						break;
					case OBSTACLE:
						m_obstacles.push_back(m_level[row][col]);
						m_visibleTile.push_back(m_level[row][col]);
						break;
					case CHECKPOINT:
						m_checkPoint.push_back(m_level[row][col]);
						m_visibleTile.push_back(m_level[row][col]);
						break;
				}
			}
		}
	}
	inFile.close();
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
	m_obstacles.clear();
	m_checkPoint.clear();
	m_visibleTile.clear();
	m_pStartingTile = nullptr;
	m_pEndTile = nullptr;
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
	for (unsigned short row = 0; row < m_rows; row++)
	{
		for (unsigned short col = 0; col < m_cols; col++)
		{
			if (m_level[row][col]->GetTag() != AIR)
				m_level[row][col]->Render();
		}
	}
}

vector<Tile*>& TiledLevel::GetObstacles() { return m_obstacles; }

void Tile::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst);
}