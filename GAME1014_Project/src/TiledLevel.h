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

enum Tag { NONE = -1 ,START, AIR ,END};

class Tile : public SpriteObject
{
public:
	Tile(SDL_Rect s, SDL_FRect d, SDL_Texture* t,bool o, bool h, Tag ta = NONE)
		:SpriteObject(s, d, t), m_obstacle(o), m_hazard(h), m_activate(false), m_tag(ta) {}
	Tile* Clone() const {	return new Tile(m_src, m_dst, m_pText ,m_obstacle, m_hazard, m_tag); }
	bool IsObstacle() const { return m_obstacle; }
	Tag GetTag() const { return m_tag; }
	void SetTag(Tag t) { m_tag = t; }
	void SetXY(float x, float y) { m_dst.x = x; m_dst.y = y; }
	void Update() {}
	void Render() {}
private:
	bool m_obstacle, m_hazard, m_activate;
	Tag m_tag;
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
	Tile* GetStartingTile() const { return m_pStartingTile; }
	XMLDocument xmlDoc;

private:
	const char* m_tileKey;
	int m_rows, m_cols;
	Tile* m_pStartingTile;
	map<char, Tile*> m_tiles; // Our map of 16 prototype Tile objects.
	vector<vector<Tile*>> m_level; // 2D vector.
	vector<Tile*> m_obstacles;
};

#endif

