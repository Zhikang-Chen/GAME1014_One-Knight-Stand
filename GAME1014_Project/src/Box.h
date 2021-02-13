#pragma once
#include "SDL.h"

class Box
{
public:
	Box(const SDL_Rect r);
	void Update();
	void Render();
	void Reset(); 

private:
	SDL_Rect m_dst;
	SDL_Rect m_startPos;
	SDL_Color m_color;
};