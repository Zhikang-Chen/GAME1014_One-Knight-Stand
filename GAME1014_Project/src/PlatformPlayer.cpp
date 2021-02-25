#include "PlatformPlayer.h"
#include <algorithm>


#include "Engine.h"
#include "EventManager.h"

//For some reason m_maxVelY can't take JUMPFORCE
//Will fix someday

PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : AnimatedSpriteObject(s, d, t, 0, 0, 13, 10),
m_state(STATE_JUMPING), m_grounded(false), m_facingLeft(false), m_secondJump(false),m_maxVelX(10.0), m_maxVelY(40.0), m_grav(GRAV), m_drag(0.85)
{
	cout << addressof(m_dst) << endl;
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	//SetAnimation(1, 8, 9); // Initialize jump animation.
}


void PlatformPlayer::Update()
{

	if (EVMA::KeyPressed(SDL_SCANCODE_H))
		ShowHitbox();
	
	// Checking states.
	switch (m_state)
	{
	case STATE_IDLING:
		// Transition to run.
		if (EVMA::KeyPressed(SDL_SCANCODE_A) || EVMA::KeyPressed(SDL_SCANCODE_D))
		{
			m_state = STATE_RUNNING;
			//SetAnimation(3, 0, 8, 256); // , 256
		}
		// Transition to jump.
		else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -JUMPFORCE; // SetAccelY(-JUMPFORCE);
			m_grounded = false; // SetGrounded(false);
			m_secondJump = true;
			m_state = STATE_JUMPING;
			//SetAnimation(1, 8, 9, 256);
		}
		break;
	case STATE_RUNNING:
		// Move left and right.
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			m_accelX = -1.5;
			if (!m_facingLeft)
				m_facingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_accelX = 1.5;
			if (m_facingLeft)
				m_facingLeft = false;
		}
		// Transition to jump.
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -JUMPFORCE;
			m_grounded = false;
			m_secondJump = true;
			m_state = STATE_JUMPING;
			//SetAnimation(1, 8, 9, 256);
		}
		// Transition to idle.
		if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_state = STATE_IDLING;
			//SetAnimation(1, 0, 1, 256); // , 256
		}
		break;
	case STATE_JUMPING:
		// Move in mid-air is cool.
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			m_accelX = -1.5;
			if (!m_facingLeft)
				m_facingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_accelX = 1.5;
			if (m_facingLeft)
				m_facingLeft = false;
		}

		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_secondJump)
		{
			m_accelY = -JUMPFORCE;
			m_grounded = false;
			m_secondJump = false;
			//SetAnimation(1, 8, 9, 256);
		}
		
		// Hit the ground, transition to run.
		if (m_grounded)
		{
			m_state = STATE_RUNNING;
			//SetAnimation(3, 0, 8, 256);
		}
		break;
	}

	
	// x axis
	m_velX += m_accelX;
	m_velX *= (m_grounded ? m_drag : 1.0f);

	
	//Velocity clamping
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX); //std::max first check, std::min second	
	m_dst.x += m_velX;
	
	// y axis
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), (m_grav * 4.0f)); //m_grav is how fast you're going to fall
	m_dst.y += m_velY;


	//Reset acceleration
	m_accelX = m_accelY = 0.0; //Similar to a keyup event
	this->Animate();
}

void PlatformPlayer::Render()
{
	if (m_showHitbox)
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_dst);
	}
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst, m_angle, 0, m_facingLeft?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
}

void PlatformPlayer::ShowHitbox()
{
	m_showHitbox = !m_showHitbox;
}

void PlatformPlayer::Stop()
{
	StopX();
	StopY();
}

void PlatformPlayer::StopX() { m_velX = 0.0; }

void PlatformPlayer::StopY() { m_velY = 0.0; }

void PlatformPlayer::SetAccelX(double a) { m_accelX = a; }

void PlatformPlayer::SetAccelY(double a) { m_accelY = a; }

bool PlatformPlayer::IsGrounded() { return m_grounded; }

bool PlatformPlayer::SetGrounded(bool g) { return m_grounded = g; }

bool PlatformPlayer::GetAlive() { return m_alive; }

void PlatformPlayer::SetAlive(bool a) { m_alive = a; }

float PlatformPlayer::GetVelX() { return m_velX; }

float PlatformPlayer::GetVelY() { return m_velY; }

void PlatformPlayer::SetX(float x) { this->GetDst()->x = x; }


void PlatformPlayer::SetY(float y) { this->GetDst()->y = y; }

