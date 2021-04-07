#pragma once
#ifndef _LABEL_H_
#define _LABEL_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "GameObject.h"

class Label : public GameObject
{
public: // Public methods.
	Label(std::string key, const float x, const float y, const char* str, const SDL_Color col = { 255,255,255,255 });
	Label(std::string key, const float x, const float y, std::string str, const SDL_Color col = { 255,255,255,255 });
	~Label();
	void Render();
	void Update() {};
	void SetText(const char* c);
	void SetText(string str);
	void SetPos(const float x, const float y);
	void SetColor(const SDL_Color& col);
	void UseFont(std::string key);
	string GetString() const;

private: // Private properties.
	TTF_Font* m_Font;
	SDL_Color m_TextColor;
	//SDL_FRect m_rTextRect;
	SDL_Texture* m_pTexture;
	char m_String[256];

};

#endif