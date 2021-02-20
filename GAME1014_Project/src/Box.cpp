#include "Box.h"
#include "Engine.h"
#include "EventManager.h"
#include <cstdlib>

Box::Box(const SDL_Rect r)
{
	m_dst = m_startPos = r;
	m_color = { 255, 255, 255, 255 };
}

void Box::Update()
{
	if (SDL_PointInRect(&EVMA::GetMousePos(), &m_dst))
	{
		if (EVMA::MouseHeld(1))
		{
			m_dst.x = EVMA::GetMousePos().x - m_dst.w/2;
			m_dst.y = EVMA::GetMousePos().y - m_dst.h/2;
		}
		if (EVMA::MousePressed(3)) // Try MouseHeld(3) instead!
		{
			m_color.r = rand() % 256;
			m_color.g = rand() % 256;
			m_color.b = rand() % 256;
		}
	}
}

void Box::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &m_dst);
}

void Box::Reset()
{
	m_dst = m_startPos;
	m_color = { 255,255,255,255 };
}

/* Raw check for point in rect:

if (mx < (m_rDst.x + m_rDst.w) && mx > m_rDst.x && // If cursor is within X bounds
	my < (m_rDst.y + m_rDst.h) && my > m_rDst.y)   // And cursor is within Y bounds
	
*/