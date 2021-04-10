#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "SDL.h"

class GameObject
{
public:
	virtual ~GameObject() = default;
	// Methods.
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual SDL_FRect* GetDst() { return &m_dst; }
	void SetEnable(bool e) { m_enable = e; }
protected: // Attributes.
	SDL_FRect m_dst;
	bool m_enable;
protected: // Methods.
	GameObject() :m_dst({ 0,0,0,0 }), m_enable(true) {}
	GameObject(const SDL_FRect d) :m_dst(d), m_enable(true) {}

};

#endif
