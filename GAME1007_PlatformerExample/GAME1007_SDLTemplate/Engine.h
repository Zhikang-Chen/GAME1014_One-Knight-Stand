#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "SDL.h"
#include <iostream>
#include "PlatformPlayer.h"
#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
using namespace std;

class Engine
{
private: // private properties.
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	//These are the dimensions of the platforms
	SDL_Rect m_platforms[5] = { {462, 648, 100, 20}, //0
							   {200, 468, 100, 20},  //1
							   {724, 468, 100, 20},  //2
							   {462, 368, 100, 40},  //3
							   {-100, 668, 1000, 100} };  //4 This is the Ground.

	PlatformPlayer m_player;
		
	

private: // private method prototypes.
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvents();
	bool KeyDown(const SDL_Scancode c);
	void CheckCollision();
	void Update();
	void Render();
	void Sleep();

public: // public method prototypes.
	int Run();
};

#endif

// Reminder: you can ONLY have declarations in headers, not logical code
