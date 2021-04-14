#include "Button.h"
#include "EventManager.h"
#include "SaveManager.h"
#include "StateManager.h"

Button::Button(SDL_Rect src, SDL_FRect dst, SDL_Texture* t)
	: SpriteObject(src, dst, t), m_state(STATE_UP) {}

bool Button::MouseCollision()
{
	const int mx = EVMA::GetMousePos().x;
	const int my = EVMA::GetMousePos().y;
	return (mx < (m_dst.x + m_dst.w) && mx > m_dst.x &&
		    my < (m_dst.y + m_dst.h) && my > m_dst.y);
}

void Button::Update()
{
	bool col = MouseCollision();
	switch (m_state)
	{
	case STATE_UP:
		if (col)   
			m_state = STATE_OVER;
		break;
	case STATE_OVER:
		if (!col)
			m_state = STATE_UP;
		else if (col && EVMA::MousePressed(1)) // 1 = left, 2 = middle, 3 = right
			m_state = STATE_DOWN;
		break;
	case STATE_DOWN:
		if (EVMA::MouseReleased(1))
		{
			if (col)
			{
				m_state = STATE_OVER;
				// Execute new "callback".
				Execute();
			}
			else 
				m_state = STATE_UP;
		}
		break;
	}
}

void Button::Render()
{
	m_src.x = m_src.w * (int)m_state;
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst);
}

// Create button subclasses and their overridden Execute methods below...

void BoolButton::Execute()
{
	m_changeState = true;
}

void PlayButton::Execute()
{
	STMA::ChangeState(new GameState);
}

void ExitButton::Execute()
{
	Engine::Instance().Running() = false;
	//exit(-1);
}

void ReturnButton::Execute()
{
	STMA::PopState();
}

void SaveButton::Execute()
{
	SAMA::OverwriteSave();
}

void LoadButton::Execute()
{
	SAMA::load();
	STMA::ChangeState(new GameState);
}

void TitleButton::Execute()
{
	STMA::ChangeState(new TitleState);
}

void NewGameButton::Execute()
{
	SAMA::resetSave();
	SAMA::load();
	STMA::ChangeState(new GameState);
}
