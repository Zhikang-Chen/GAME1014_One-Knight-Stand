#pragma once
#ifndef _TILEDLEVEL_H_
#define _TILEDLEVEL_H_

#include <map>
#include <vector>
#include "Enemy.h"
#include "GameObject.h"
#include "ItemObject.h"
#include "SpriteObject.h"
#include "TextureManager.h"
#include "tinyxml2.h"

using namespace tinyxml2;

enum Tag { NONE = -1, SPAWN, END, AIR, OBSTACLE, HAZARD, CHECKPOINT, PLATFORM };

class Tile : public SpriteObject
{
public:
	Tile(SDL_Rect s, SDL_FRect d, SDL_Texture* t, Tag ta = NONE)
		:SpriteObject(s, d, t), m_activate(false), m_tag(ta) {}
	virtual Tile* Clone() const { return new Tile(m_src, m_dst, m_pText, m_tag); }

	Tag GetTag() const { return m_tag; }

	virtual void Activate() { m_activate = true; }
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
	SpawnTile(SDL_Rect s, SDL_FRect d, SDL_Texture* t = TEMA::GetTexture("Spawn"))
		:Tile(s,d,t, SPAWN) { }
	SpawnTile* Clone() const { return new SpawnTile(m_src, m_dst); }
};

class EndTile : public Tile
{
public:
	EndTile(SDL_Rect s, SDL_FRect d, SDL_Texture* t = TEMA::GetTexture("End"))
		:Tile(s, d, t, END) { }
	EndTile* Clone() const { return new EndTile(m_src, m_dst); }
};

class CheckPointTile : public Tile
{
public:
	CheckPointTile(SDL_Rect s, SDL_FRect d, SDL_Texture* t = TEMA::GetTexture("On off"))
		:Tile(s, d, t, CHECKPOINT) { }
	CheckPointTile* Clone() const { return new CheckPointTile(m_src, m_dst); }
	void Activate() override;
};

class TiledLevel : public GameObject
{
public:
	TiledLevel(const unsigned short r, const unsigned short c, const int w, const int h,
		const char* tileData, const char* levelData, const char* tileKey);
	~TiledLevel();
	void Update(); // Empty.
	void Render();
	vector<Enemy*>& GetEnemy();
	vector<Tile*>& GetObstacles();
	vector<Tile*>& GetCheckPoint() { return m_checkPoint; }
	vector<Tile*>& GetVisibleTile() { return m_visibleTile; }
	vector<Tile*>& GetRenderTile() { return m_renderTile; }
	vector<HealthPotion*>& GetPotion() { return m_potions; }
	void AddPotion(HealthPotion* p);
	
	vector<vector<Tile*>>& GetAllTile() { return m_level; }
	Tile* GetStartingTile() const { return m_pStartingTile; }
	XMLDocument xmlDoc;

private:
	const char* m_tileKey;
	int m_rows, m_cols;
	Tile* m_pStartingTile;
	map<char, Tile*> m_tiles; // Our map of 16 prototype Tile objects.
	vector<vector<Tile*>> m_level; // 2D vector.
	vector<Tile*> m_checkPoint;
	vector<Tile*> m_renderTile;
	vector<Tile*> m_visibleTile;
	vector<HealthPotion*> m_potions;
	vector<Enemy*> m_enemy;
};

#endif

