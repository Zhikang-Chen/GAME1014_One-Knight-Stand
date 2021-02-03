#include "PlatformPlayer.h"
#include <algorithm>


PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Renderer* r, SDL_Texture* t) : AnimatedSprite(s, d, r, t, 0, 0, 13, 10){}


void PlatformPlayer::Init()
{
	m_grounded = false;
	m_alive = true;
	m_showHitbox = false;
	m_accelX = m_accelY = m_velX = m_velY = 0.0; //All of these have a value of 0. Value is passed down
	m_maxVelX = 10.0;
	m_maxVelY = JUMPFORCE;
	m_grav = GRAV;
	m_drag = 0.88;
}

void PlatformPlayer::Update()
{
	// x axis
	m_velX += m_accelX;
	m_velX *= (m_grounded ? m_drag : 1.0);

	//Velocity clamping
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX); //std::max first check, std::min second
	this->GetDstP()->x += (int)m_velX;
	// y axis

	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), (m_grav * 4.0)); //m_grav is how fast you're going to fall
	this->GetDstP()->y += (int)m_velY;

	//Reset acceleration
	m_accelX = m_accelY = 0.0; //Similar to a keyup event
	this->Animate();
}

void PlatformPlayer::Render()
{
	if (m_showHitbox)
	{
		SDL_SetRenderDrawColor(m_pRend, 255, 0, 0, 255);
		SDL_RenderFillRect(m_pRend, &MAMA::ConvertFRect2Rect(this->GetDst()));
	}
	SDL_RenderCopyExF(m_pRend, m_pText, GetSrcP(), GetDstP(), m_angle, 0, SDL_FLIP_NONE);
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

double PlatformPlayer::GetVelX() { return m_velX; }

double PlatformPlayer::GetVelY() { return m_velY; }

void PlatformPlayer::SetX(float x) { this->GetDstP()->x = x; }


void PlatformPlayer::SetY(float y) { this->GetDstP()->y = y; }

