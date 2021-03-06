#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"
#include <iostream>

#include "Engine.h"
#include "GameObject.h"

class SpriteObject : public GameObject // Inline class.
{
public: // Inherited and public.
	SpriteObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t)
		:m_src(s), GameObject(d), m_pText(t), m_angle(0.0) {}
	virtual void Update() {};
	virtual void Render()
	{
		if(m_enable)
			SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, GetSrc(), GetDst(), m_angle, 0, SDL_FLIP_NONE);
	}
	
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Texture* GetTexture() { return m_pText; }
	double& GetAngle() { return m_angle; }
	void SetAngle(double a) { m_angle = a; }
protected: // Private BUT inherited.
	double m_angle;
	SDL_Rect m_src;
	SDL_Texture* m_pText;
private: // Private NOT inherited.
};

class AnimatedSpriteObject : public SpriteObject// Also inline.
{
public:
	AnimatedSpriteObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t, int sstart, int smin, int smax, int nf)
		:SpriteObject(s, d, t), m_sprite(sstart), m_spriteMin(smin), m_spriteMax(smax), m_frameMax(nf) {}

protected:
	void SetAnimation(const unsigned short fMax, const unsigned short sMin, const unsigned short sMax, const int srcY = 0)
	{
		m_frame = 0;
		m_frameMax = fMax;
		m_sprite = m_spriteMin = sMin;
		m_spriteMax = sMax;
		m_src.x = m_src.w * m_sprite;
		m_src.y = srcY;
	}
	void Animate()
	{
		if (m_frame++ == m_frameMax) // Post-increment ensures m_frame starts at 0.
		{
			m_frame = 0;
			if (m_sprite++ == m_spriteMax)
				m_sprite = m_spriteMin;
		}
		m_src.x = m_src.w * m_sprite;
	}

	int m_sprite,		// The current sprite index in row.
		m_spriteMin,	// The sprite index to start animation on.
		m_spriteMax,	// The sprite index to end animation on.
		m_frame = 0,	// Frame counter.
		m_frameMax;		// Number of frames to display each sprite.
};

/* Note: A lot of animation methods use a modulus operation to wrap the frames
   around, but I am not. I may have different cycles on the same row and so I
   want total control over my animations without having it look too complex. */

#endif