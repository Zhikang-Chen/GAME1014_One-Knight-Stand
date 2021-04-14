#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "SpriteObject.h"
#include <SDL.h>
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
class BoolButton final : public Button
{
public:
	BoolButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t), m_changeState(false) {}
	bool GetChangeState() { return m_changeState; }
private:
	bool m_changeState;
	void Execute() override;
};


// Button that change state to Play
class PlayButton final : public Button
{
public:
	PlayButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t) {}
private:
	void Execute() override;
};

// Button that exit the game
class ExitButton final : public Button
{
public:
	ExitButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t) {}
private:
	void Execute() override;
};

// Button that return to game
class ReturnButton final : public Button
{
public:
	ReturnButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t) {}
private:
	void Execute() override;
};

// Button that save the game
class SaveButton final : public Button
{
public:
	SaveButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t) {}
private:
	void Execute() override;
};

// Button that save the game
class LoadButton final : public Button
{
public:
	LoadButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t) {}
private:
	void Execute() override;
};

// Button that save the game
class TitleButton final : public Button
{
public:
	TitleButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t) {}
private:
	void Execute() override;
};

// Button that reset save
class NewGameButton final : public Button
{
public:
	NewGameButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t) : Button(src, dst, t) {}
private:
	void Execute() override;
};

#endif