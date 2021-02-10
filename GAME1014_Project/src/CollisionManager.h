#pragma once
#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include <iostream>
#include <SDL.h>
#include "MathManager.h"

class CollisionManager
{
public:
	// AABB-AABB overloads.
	static bool AABBCheck(const SDL_Rect& object1, const SDL_Rect& object2); // Two int-based Rects.
	static bool AABBCheck(const SDL_Rect& object1, const SDL_FRect& object2); // Int-based Rect, Float-based Rect.
	static bool AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2); // Two float-based Rects.

	static bool CircleCircleCheck(const SDL_FPoint object1, const SDL_FPoint object2, const double r1, const double r2 = 0.0);
	static bool CircleAABBCheck(const SDL_FPoint object1, const double r, const SDL_FRect& object2);

	static bool LinePointCheck(const SDL_FPoint object1_start, const SDL_FPoint object1_end, const SDL_FPoint object2);
private:
	CollisionManager() {}
};

typedef CollisionManager COMA;

#endif