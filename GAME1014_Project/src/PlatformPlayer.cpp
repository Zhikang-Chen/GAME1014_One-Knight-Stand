#include "PlatformPlayer.h"
#include <algorithm>
#include "Engine.h"
#include "EventManager.h"
#include "SoundManager.h"

//For some reason m_maxVelY can't take JUMPFORCE
//Will fix someday

PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : AnimatedSpriteObject(s, d, t, 0, 0, 22, 10),
m_state(STATE_IDLING), m_grounded(false), m_facingLeft(false), m_secondJump(false),m_maxVelX(10.0), m_maxVelY(40.0), m_grav(GRAV), m_drag(0.85)
{
	//cout << addressof(m_dst) << endl;
	m_pBoundingBox = SDL_FRect({m_dst.x,m_dst.y,40,60 });
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	m_curHealth = m_maxHealth = 5;
	SetAnimation(9, 13, 21);
	//SetAnimation(1, 8, 9); // Initialize jump animation.
}


void PlatformPlayer::Update()
{

	//Load Sound effects
	SoundManager::Load("Aud/sword_swing.wav", "slash", SOUND_SFX);
	SoundManager::Load("Aud/ice_slash.wav", "specSlash", SOUND_SFX);
	

	//Set Sound Volume
	SoundManager::SetSoundVolume(30);

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
			SetAnimation(6, 6, 12); // , 256


		}
		else if (EVMA::KeyPressed(SDL_SCANCODE_J))
		{
			m_state = STATE_ATTACKING;
			SetAnimation(5, 0, 5);
			
			SoundManager::PlaySound("slash", 0, 0);
		
		}

		//ADDED A BUTTON to use weapon ability
		else if (EVMA::KeyPressed(SDL_SCANCODE_Q))
		{
			m_state = STATE_SPECIAL_ATTACK;
			//SetAnimation()
			SetAnimation(4, 23, 26);

			SoundManager::PlaySound("specSlash", 0, 0);

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
			SetAnimation(9, 13, 22);
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
		// Hit the ground, transition to run.
		if (m_grounded)
		{
			m_state = STATE_RUNNING;
			//SetAnimation(3, 0, 8, 256);
		}
		break;

	case STATE_ATTACKING:
		// The best way to fix this is frame counter.
		// I am too lazy to make it
		if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D) && !EVMA::KeyDown(SDL_SCANCODE_J))
		{
			m_state = STATE_IDLING;
			SetAnimation(9, 13, 22);
		}
		break;

	case STATE_SPECIAL_ATTACK:
		
		if (!EVMA::KeyHeld(SDL_SCANCODE_Q))
		{
			m_state = STATE_IDLING;
			SetAnimation(9, 13, 22);
		}

	}

	
	// x axis
	m_velX += m_accelX;
	m_velX *= (m_grounded ? m_drag : 1.0f);

	
	//Velocity clamping
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX); //std::max first check, std::min second	
	m_pBoundingBox.x += m_velX;
	
	// y axis
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), (m_grav * 4.0f)); //m_grav is how fast you're going to fall
	m_pBoundingBox.y += m_velY;


	//Reset acceleration
	m_accelX = m_accelY = 0.0; //Similar to a keyup event

	// For some reason when the player face left dst is 3 pixel off
	// No idea what cause it but it does cause problem
	if (m_facingLeft)
		m_dst.x = m_pBoundingBox.x - m_pBoundingBox.w + 3;
	else if(!m_facingLeft)
		m_dst.x = m_pBoundingBox.x;

	
	m_dst.y = m_pBoundingBox.y - 9;
	
	this->Animate();
}

void PlatformPlayer::Render()
{
	if (m_showHitbox)
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_dst);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_pBoundingBox);
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

PlayerState PlatformPlayer::GetState() { return m_state; }

SDL_FRect* PlatformPlayer::GetBoundingBox() { return &m_pBoundingBox; }

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

void PlatformPlayer::SetX(float x) { m_pBoundingBox.x = x; }

void PlatformPlayer::SetY(float y) { m_pBoundingBox.y = y; }

int PlatformPlayer::GetHeath(){ return m_curHealth; }

int PlatformPlayer::GetMaxHealth() { return m_maxHealth; }

void PlatformPlayer::SetHeath(int h) { m_curHealth = h; }

void PlatformPlayer::SetMaxHealth(int h) { m_maxHealth = h; }

