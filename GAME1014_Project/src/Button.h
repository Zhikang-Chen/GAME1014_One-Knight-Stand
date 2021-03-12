#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "SpriteObject.h"
#include <SDL.h>
#include "Button.h"
#include "Label.h"
#include "TextureManager.h"

// Button will be an example of the command design pattern.
class Button : public SpriteObject
{
public: // Public methods.
	void Update();
	void Render();
protected: // Private but inherited!
	Button(SDL_Rect src, SDL_FRect dst, SDL_Texture* t);
	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state;
	bool MouseCollision();
	virtual void Execute() = 0; // Pure virtual method, meaning Button is now an abstract class (interface)!
};

// List button subclasses here...

// Button that return true or false
class BoolButton : public Button
{
public:
	BoolButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t), m_changeState(false) {}
	bool GetChangeState() { return m_changeState; }
private:
	bool m_changeState;
	void Execute() override;
};


//class LabelButton : public Label
//{
//public:
//	LabelButton(std::string key, const float x, const float y, const char* str) : Label(key,x,y,str)
//	{
//		l = new Label(key, x, y, str);
//		
//	}
//	
//
//private:
//	Label* l;
//	void Execute() override {};
//};

#endif