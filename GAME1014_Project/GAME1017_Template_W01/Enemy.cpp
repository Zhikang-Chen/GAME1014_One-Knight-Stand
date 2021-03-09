#include "Enemy.h"

#include "Engine.h"

Enemy::Enemy(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : AnimatedSpriteObject(s, d, t, 0, 0, 0, 0),
m_grounded(false), m_maxVelX(10.0), m_maxVelY(60.0), m_grav(GRAV), m_drag(0.8), m_health(1)
{
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
	 
bool Enemy::GetAlive() { return m_alive; }
	 
void Enemy::SetAlive(bool a) { m_alive = a; }
	 
double Enemy::GetVelX() { return m_velX; }
	 
double Enemy::GetVelY() { return m_velY; }
	 
void Enemy::SetX(float x) { this->GetDst()->x = x; }

void Enemy::SetY(float y) { this->GetDst()->y = y; }

void Enemy::LoseHealth(int h) { m_health -= h; } //Send the player's weapon damage in as argument
