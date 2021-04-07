#include "Engine.h"
#include "Label.h"
#include "FontManager.h"
#include <iostream>
#include <cstring>

Label::Label(std::string key, const float x, const float y, const char* str,
	const SDL_Color col) :m_TextColor(col)
{
	m_Font = FontManager::GetFont(key);
	SetPos(x, y);
	SetText(str);
}

Label::Label(std::string key, const float x, const float y, string str,
	const SDL_Color col) :m_TextColor(col)
{
	m_Font = FontManager::GetFont(key);
	SetPos(x, y);
	SetText(str);
}

Label::~Label()
{
	SDL_DestroyTexture(m_pTexture);
}

void Label::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pTexture, 0, &m_dst);
}

void Label::SetText(const char* str)
{
	strcpy_s(m_String, 256, str);
	SDL_Surface* fontSurf;
	if (!(fontSurf = TTF_RenderText_Solid(m_Font, m_String, m_TextColor)))
	{
		cout << TTF_GetError() << endl;
	}
	else
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), fontSurf);
		m_dst = { m_dst.x, m_dst.y, (float)fontSurf->w, (float)fontSurf->h };
		SDL_FreeSurface(fontSurf);
	}
}

void Label::SetText(string str)
{
	strcpy_s(m_String, 256, str.c_str());
	//m_String = str.c_str();
	SDL_Surface* fontSurf;
	if (!(fontSurf = TTF_RenderText_Solid(m_Font, m_String, m_TextColor)))
	{
		cout << TTF_GetError() << endl;
	}
	else
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), fontSurf);
		m_dst = { m_dst.x, m_dst.y, (float)fontSurf->w, (float)fontSurf->h };
		SDL_FreeSurface(fontSurf);
	}
}

void Label::SetPos(const float x, const float y)
{
	m_dst = { x, y, m_dst.w, m_dst.h };
}

void Label::SetColor(const SDL_Color& col)
{
	m_TextColor = col;
	SetText(m_String);
}

void Label::UseFont(std::string key)
{
	SetText(m_String);
}

string Label::GetString() const
{
	return m_String;
}
