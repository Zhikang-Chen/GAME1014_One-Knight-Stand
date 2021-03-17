#include "Enemy.h"
#include "Engine.h"

Enemy::Enemy(SDL_Rect s, SDL_FRect d, SDL_Texture* t, int sstart, int smin, int smax, int nf) : AnimatedSpriteObject(s, d, t, sstart, smin, smax, nf),
m_grounded(false), m_maxVelX(10.0), m_maxVelY(40.0), m_grav(GRAV), m_drag(0.85), m_health(1)
{
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
}

void Enemy::Stop()
{
	StopX();
	StopY();
}

void Enemy::StopX() { m_velX = 0.0; }
	 
void Enemy::StopY() { m_velY = 0.0; }
	 
void Enemy::SetAccelX(double a) { m_accelX = a; }
	 
void Enemy::SetAccelY(double a) { m_accelY = a; }

bool Enemy::IsGrounded() { return m_grounded; }

bool Enemy::SetGrounded(bool g) { return m_grounded = g; }
	 
float Enemy::GetVelX() { return m_velX; }
	 
float Enemy::GetVelY() { return m_velY; }
	 
void Enemy::SetX(float x) { this->GetDst()->x = x; }

void Enemy::SetY(float y) { this->GetDst()->y = y; }

void Enemy::Update()
{
	//m_accelY = -JUMPFORCE;
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
	
}

void Enemy::Render() {}

void Enemy::LoseHealth() { m_health -= 1; } //Send the player's weapon damage in as argument
