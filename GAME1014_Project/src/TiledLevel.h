#pragma once
#ifndef _TILEDLEVEL_H_
#define _TILEDLEVEL_H_

#include <fstream>
#include <map>
#include <vector>
#include "Engine.h"
#include "GameObject.h"
#include "SpriteObject.h"
#include "TextureManager.h"
#include "tinyxml2.h"

using namespace tinyxml2;

enum Tag { NONE = -1 ,SPAWN, END, AIR, OBSTACLE, HAZARD, CHECKPOINT };

class Tile : public SpriteObject
{
public:
	Tile(SDL_Rect s, SDL_FRect d, SDL_Texture* t, Tag ta = NONE)
		:SpriteObject(s, d, t), m_activate(false), m_tag(ta) {}
	Tile* Clone() const { return new Tile(m_src, m_dst, m_pText, m_tag); }

	Tag GetTag() const { return m_tag; }

	void Activate() { m_activate = !m_activate; }
	bool GetActivate() { return m_activate; }
	
	void SetTag(Tag t) { m_tag = t; }
	void SetXY(float x, float y) { m_dst.x = x; m_dst.y = y; }
	void Update() {};
	void Render();
protected:
	bool m_activate;
	Tag m_tag;
};

class SpawnTile : public Tile
{
public:
	SpawnTile(SDL_Rect s, SDL_FRect d, SDL_Texture* t = TEMA::GetTexture("Spawn"), Tag ta = SPAWN)
		:Tile(s,d,t,ta) { }
	SpawnTile* Clone() const { return new SpawnTile(m_src, m_dst); }
};

class EndTile : public Tile
{
public:
	EndTile(SDL_Rect s, SDL_FRect d, SDL_Texture* t = TEMA::GetTexture("End"), Tag ta = END)
		:Tile(s, d, t, ta) { }
	EndTile* Clone() const { return new EndTile(m_src, m_dst); }
};

class TiledLevel : public GameObject
{
public:
	TiledLevel(const unsigned short r, const unsigned short c, const int w, const int h,
		const char* tileData, const char* levelData, const char* tileKey);
	~TiledLevel();
	void Update() {} // Empty.
	void Render();
	vector<Tile*>& GetObstacles();
	vector<Tile*>& GetCheckPoint() { return m_checkPoint; }
	vector<Tile*>& GetVisibleTile() { return m_visibleTile; }
	vector<vector<Tile*>>& GetAllTile() { return m_level; }
	Tile* GetStartingTile() const { return m_pStartingTile; }
	Tile* GetEndTile() const { return m_pEndTile; }
	XMLDocument xmlDoc;

private:
	const char* m_tileKey;
	int m_rows, m_cols;
	Tile* m_pStartingTile;
	Tile* m_pEndTile;
	map<char, Tile*> m_tiles; // Our map of 16 prototype Tile objects.
	vector<vector<Tile*>> m_level; // 2D vector.
	vector<Tile*> m_checkPoint; 
	vector<Tile*> m_obstacles;
	vector<Tile*> m_visibleTile;
};

#endif

