#include "Slime.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "SoundManager.h"

Slime::Slime(SDL_Rect s, SDL_FRect d) : Enemy(s, d, TEMA::GetTexture("Slime"))
{
	m_maxHealth = m_curHealth = 5;
	m_jumpTimer = 0;
}

void Slime::Move()
{
	m_jumpTimer++;
	if(m_jumpTimer >= 120)
	{
		m_grounded = false;
		SoundManager::PlaySound("bounce", 0, 3);
		m_jumpTimer = 0;
		if(m_facingLeft)
			m_accelX = 30.0f;
		else
			m_accelX = -30.0f;
		m_accelY = -JUMPFORCE; // SetAccelY(-JUMPFORCE);
	}
	else if(m_jumpTimer >= 110)
	{
		SetColour(180, 180, 255);
	}
	else if(m_grounded)
	{
		SetColour(255, 255, 255);
	}



	//m_accelY = JUMPFORCE;
}

bool Slime::DropTable(int r)
{
	//For now, it will always return true so it will always drop an item
	//But if we want chances, then we'd uncomment the stuff.
	if (r < 39)
	return true;
	else
		return false;
}