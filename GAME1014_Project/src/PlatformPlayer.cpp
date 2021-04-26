#include "PlatformPlayer.h"
#include <algorithm>

#include "Bullet.h"
#include "Engine.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

//For some reason m_maxVelY can't take JUMPFORCE
//Will fix someday

PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : EntityObject(s, d, t),
 m_grounded(false), m_state(PlayerState::STATE_IDLING)
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
	//SetAnimation(9, 13, 22);
	SetAnimation(9, 0, 9, m_src.h * 2);
	//Load Sound effects
	SoundManager::Load("Aud/jump.wav", "jump", SOUND_SFX);
	SoundManager::Load("Aud/sword_swing.wav", "slash", SOUND_SFX);
	SoundManager::Load("Aud/ice_slash.wav", "specSlash", SOUND_SFX);
	SoundManager::Load("Aud/cooldownActivate.wav", "cdActive", SOUND_SFX);
	SoundManager::Load("Aud/ding.wav", "cdActive", SOUND_SFX);
	SoundManager::Load("Aud/whip.wav", "whip", SOUND_SFX);

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/icebullet.png", "b");
}

PlatformPlayer::~PlatformPlayer()
{
	for(auto &i : m_projectile)
	{
		delete i;
		i = nullptr;
	}
	m_projectile.clear();
}

void PlatformPlayer::Update()
{
	//Set Sound Volume
	SoundManager::SetSoundVolume(30);
	if (EVMA::KeyPressed(SDL_SCANCODE_H))
		ShowHitbox();

	
	if (m_isSkillUp && skillTimer / 500 >= 1)
	{
		SoundManager::PlaySound("cdActive", 0, 0);
		skillTimer = 0;
		m_isSkillUp = false;
	}
	else
	{
		skillTimer++;
	}
	if (m_isSkillUpSTUN && skillSTUNTimer / 400 >= 1)
	{
		SoundManager::PlaySound("cdActive", 0, 0);
		skillSTUNTimer = 0;
		m_isSkillUpSTUN = false;
	}
	else
	{
		skillSTUNTimer++;
	}
	
	switch (m_state)
	{
		case PlayerState::STATE_IDLING:
		{
			// Transition to run.
			if (EVMA::KeyPressed(SDL_SCANCODE_A) || EVMA::KeyPressed(SDL_SCANCODE_D))
			{
				m_state = PlayerState::STATE_RUNNING;
				SetAnimation(6, 0, 7, m_src.h*1); // , 256
			}

			if (EVMA::KeyPressed(SDL_SCANCODE_J) || EVMA::MousePressed(1))
			{
				m_state = PlayerState::STATE_ATTACKING;
				SetAnimation(5, 0, 4, m_src.h * 0);
				SoundManager::PlaySound("slash", 0, 0);
				m_currentAttack = AttackType::NORMAL;
			}
			//ADDED A BUTTON to use weapon ability
			if (!m_isSkillUp)
			{
				if (EVMA::KeyPressed(SDL_SCANCODE_K))
				{
					m_state = PlayerState::STATE_ATTACKING;
					//SetAnimation()
					SetAnimation(4, 0, 3, m_src.h * 3);
					SoundManager::PlaySound("specSlash", 0, 0);
					m_isSkillUp = true;
					m_currentAttack = AttackType::ICE;

					int w, h;
					SDL_QueryTexture(TEMA::GetTexture("b"), nullptr, nullptr, &w, &h);

					float x;
					if (m_facingLeft)
						x = m_dst.x - 100;
					else
						x = m_dst.x + 100;
					
					m_projectile.push_back(new Bullet({ 0,0,w,h }, { m_dst.x,m_dst.y,float(w),float(h) }, TEMA::GetTexture("b"), { x,m_dst.y }));
				}
			}
			if (!m_isSkillUpSTUN)
			{
				if (EVMA::KeyPressed(SDL_SCANCODE_L))
				{
					m_state = PlayerState::STATE_ATTACKING;
					//SetAnimation()
					SetAnimation(5, 0, 4, m_src.h * 4);
					SoundManager::PlaySound("whip", 0, 0); // no bonk sound 
					m_isSkillUpSTUN = true;
					m_currentAttack = AttackType::BONK;
				}
			}

			// Transition to jump.
			if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
			{
				SoundManager::PlaySound("jump", 0, 0);
				m_accelY = -JUMPFORCE; // SetAccelY(-JUMPFORCE);
				m_grounded = false; // SetGrounded(false);
				m_state = PlayerState::STATE_JUMPING;
				//SetAnimation(1, 8, 9, 256);
			}
			break;
		}
		case PlayerState::STATE_RUNNING:
		{
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
				m_state = PlayerState::STATE_ATTACKING;
				SetAnimation(5, 0, 4, m_src.h * 0);
				SoundManager::PlaySound("slash", 0, 0);
				m_currentAttack = AttackType::NORMAL;
			}
				
			
			// Transition to jump.
			if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
			{
				SoundManager::PlaySound("jump", 0, 0);
				m_accelY = -JUMPFORCE;
				m_grounded = false;
				m_state = PlayerState::STATE_JUMPING;
				//SetAnimation(1, 8, 9, 256);
			}

			// Transition to idle.
			if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
			{
				m_accelX = 0;
				m_state = PlayerState::STATE_IDLING;
				SetAnimation(9, 0, 9, m_src.h * 2);
			}
			break;
		}
		case PlayerState::STATE_JUMPING:
		{
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
				m_state = PlayerState::STATE_ATTACKING;
				SetAnimation(5, 0, 4, m_src.h * 0);
				SoundManager::PlaySound("slash", 0, 0);
				m_currentAttack = AttackType::NORMAL;
			}
			// Hit the ground, transition to run.
			if (m_grounded)
			{
				m_state = PlayerState::STATE_RUNNING;
				SetAnimation(6, 0, 7, m_src.h * 1); // , 256
				//SetAnimation(3, 0, 8, 256);
			}
			break;
		}
		case PlayerState::STATE_ATTACKING:
		{
			if (m_facingLeft)
				m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x - m_pBoundingBox.w + 3,m_pBoundingBox.y,35,50 });
			else if (!m_facingLeft)
				m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x + m_pBoundingBox.w + 3,m_pBoundingBox.y,35,50 });
			m_pAttackHitBox.y = m_pBoundingBox.y;

			if ((m_sprite >= m_spriteMax / 2) && (EVMA::KeyHeld(SDL_SCANCODE_A) || EVMA::KeyHeld(SDL_SCANCODE_D)))
			{
				m_state = PlayerState::STATE_RUNNING;
				//SetAnimation(9, 13, 22);
				SetAnimation(6, 0, 7, m_src.h * 1); // , 256
				m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x,m_pBoundingBox.y,0,0 });
				m_currentAttack = AttackType::NONE;
			}

			if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
			{
				m_state = PlayerState::STATE_JUMPING;
				m_accelY = -JUMPFORCE;
				m_grounded = false;
				m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x,m_pBoundingBox.y,0,0 });
				m_currentAttack = AttackType::NONE;
			}

			if (m_sprite == m_spriteMax)
			{
				m_state = PlayerState::STATE_IDLING;
				m_pAttackHitBox = SDL_FRect({ m_pBoundingBox.x,m_pBoundingBox.y,0,0 });
				SetAnimation(6, 0, 7, m_src.h * 2); // , 256
				m_currentAttack = AttackType::NONE;
			}
			break;	
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

	for (auto i : m_projectile)
	{
		i->Update();
		if(i->GetDst()->x > WIDTH + WIDTH / 2 || i->GetDst()->x < 0 - WIDTH / 2)
		{
			Remove(i);
			cout << "a" << endl;
		}
	}
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

		for (auto i : m_projectile)
		{
			SDL_RenderFillRectF(Engine::Instance().GetRenderer(), i->GetDst());
		}
	}
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst, m_angle, 0, m_facingLeft?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
	for (auto i : m_projectile)
		i->Render();
}

void PlatformPlayer::ShowHitbox()
{
	m_showHitbox = !m_showHitbox;
}

void PlatformPlayer::Remove(Projectile* object)
{
	auto i = find(m_projectile.begin(), m_projectile.end(), object);
	if(i != m_projectile.end())
	{
		m_projectile.erase(i);
		m_projectile.shrink_to_fit();
		delete object;
	}
	else
	{
		cout << "Unable find projectile" << endl;
	}
}

void PlatformPlayer::SetX(float x) { m_pBoundingBox.x = x; }

void PlatformPlayer::SetY(float y) { m_pBoundingBox.y = y; }

PlayerState PlatformPlayer::GetState() { return m_state; }

SDL_FRect* PlatformPlayer::GetAttackHitBox() { return &m_pAttackHitBox; }

AttackType PlatformPlayer::GetCurrentAttack() const
{
	return m_currentAttack;
}

vector<Projectile*> &PlatformPlayer::GetProjectiles()
{
	return m_projectile;
}

bool PlatformPlayer::IsGrounded() { return m_grounded; }

bool PlatformPlayer::SetGrounded(bool g) { return m_grounded = g; }