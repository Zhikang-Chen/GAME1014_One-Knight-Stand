#include "PlatformPlayer.h"
#include <algorithm>
#include "Engine.h"
#include "EventManager.h"
#include "SoundManager.h"

//For some reason m_maxVelY can't take JUMPFORCE
//Will fix someday

PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : EntityObject(s, d, t),
 m_grounded(false), m_state(STATE_IDLING)
{
	//cout << addressof(m_dst) << endl;
	m_pBoundingBox = SDL_FRect({m_dst.x,m_dst.y,40,60 });
	m_facingLeft = false;
	m_maxVelX = 10;
	m_maxVelY = 40;
	m_grav = GRAV;
	m_drag = 0.85;
	
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	m_curHealth = m_maxHealth = 5;
	SetAnimation(9, 13, 22);
	//Load Sound effects
	SoundManager::Load("Aud/sword_swing.wav", "slash", SOUND_SFX);
	SoundManager::Load("Aud/ice_slash.wav", "specSlash", SOUND_SFX);
}


void PlatformPlayer::Update()
{
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
		
		if (EVMA::KeyPressed(SDL_SCANCODE_J) || EVMA::MousePressed(1))
		{
			m_state = STATE_ATTACKING;
			SetAnimation(5, 0, 5);
			SoundManager::PlaySound("slash", 0, 0);
		}
		//ADDED A BUTTON to use weapon ability
		if (EVMA::KeyPressed(SDL_SCANCODE_K))
		{
			m_state = STATE_SPECIAL_ATTACK;
			//SetAnimation()
			SetAnimation(4, 23, 26);

			SoundManager::PlaySound("specSlash", 0, 0);

		}

		// Transition to jump.
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -JUMPFORCE; // SetAccelY(-JUMPFORCE);
			m_grounded = false; // SetGrounded(false);
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
		
		if (EVMA::KeyPressed(SDL_SCANCODE_J) || EVMA::MousePressed(1))
		{
			m_state = STATE_ATTACKING;
			SetAnimation(5, 0, 5);
			SoundManager::PlaySound("slash", 0, 0);
		}
		// Transition to jump.
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -JUMPFORCE;
			m_grounded = false;
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
		
		if (EVMA::KeyPressed(SDL_SCANCODE_J) || EVMA::MousePressed(1))
		{
			m_state = STATE_ATTACKING;
			SetAnimation(5, 0, 5);
			SoundManager::PlaySound("slash", 0, 0);

		}
		
		// Hit the ground, transition to run.
		if (m_grounded)
		{
			m_state = STATE_RUNNING;
			SetAnimation(6, 6, 12); // , 256
			//SetAnimation(3, 0, 8, 256);
		}
		break;

	case STATE_ATTACKING:
		
		if (m_facingLeft)
			m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x - m_pBoundingBox.w + 3,m_pBoundingBox.y,35,50 });
		else if (!m_facingLeft)
			m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x + m_pBoundingBox.w + 3,m_pBoundingBox.y,35,50 });
		m_pAttackHitBox.y = m_pBoundingBox.y;

		if ((m_sprite >= m_frameMax / 2) && (EVMA::KeyHeld(SDL_SCANCODE_A) || EVMA::KeyHeld(SDL_SCANCODE_D)))
		{
			m_state = STATE_RUNNING;
			//SetAnimation(9, 13, 22);
			SetAnimation(9, 13, 22);
			m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x,m_pBoundingBox.y,0,0 });
		}
		
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_state = STATE_JUMPING;
			m_accelY = -JUMPFORCE;
			m_grounded = false;
			m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x,m_pBoundingBox.y,0,0 });
		}
		
		if(m_sprite == m_frameMax)
		{
			m_state = STATE_IDLING;
			m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x,m_pBoundingBox.y,0,0 });
			SetAnimation(9, 13, 22);
		}
		
		break;

	case STATE_SPECIAL_ATTACK:
		
		if (m_facingLeft)
			m_pSAttackHitBox = SDL_FRect({ m_pBoundingBox.x - m_pBoundingBox.w + 3,m_pBoundingBox.y,35,50 });
		else if (!m_facingLeft)
			m_pSAttackHitBox = SDL_FRect({ m_pBoundingBox.x + m_pBoundingBox.w + 3,m_pBoundingBox.y,35,50 });
		m_pSAttackHitBox.y = m_pBoundingBox.y;

		if (!EVMA::KeyHeld(SDL_SCANCODE_K))
		{
			m_state = STATE_IDLING;
			m_pSAttackHitBox = SDL_FRect({ m_pBoundingBox.x,m_pBoundingBox.y,0,0 });
			SetAnimation(9, 13, 22);
		}
		break;
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
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_pAttackHitBox);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_pSAttackHitBox);
	}
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst, m_angle, 0, m_facingLeft?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
}

void PlatformPlayer::ShowHitbox()
{
	m_showHitbox = !m_showHitbox;
}

void PlatformPlayer::SetX(float x) { m_pBoundingBox.x = x; }

void PlatformPlayer::SetY(float y) { m_pBoundingBox.y = y; }

PlayerState PlatformPlayer::GetState() { return m_state; }

SDL_FRect* PlatformPlayer::GetAttackHitBox() { return &m_pAttackHitBox; }

SDL_FRect* PlatformPlayer::GetSAttackHitBox() { return &m_pSAttackHitBox; }

bool PlatformPlayer::IsGrounded() { return m_grounded; }

bool PlatformPlayer::SetGrounded(bool g) { return m_grounded = g; }