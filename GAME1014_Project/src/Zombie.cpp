#include "Zombie.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "SoundManager.h"

Zombie::Zombie(SDL_Rect s, SDL_FRect d) : Enemy(s, d, TEMA::GetTexture("Zombie"))
{
	m_maxHealth = 7;
	m_curHealth = 7;
}

void Zombie::Move()
{
	m_zSoundCount++;
	if (m_zSoundCount >= 100)
	{
		SoundManager::PlaySound("zombie", 0, 3);
		m_zSoundCount = 0;
	}

		//The zombie will slowly approach the player.
		if (m_facingLeft)
			m_accelX = 0.2f;
			
		else
			m_accelX = -0.2f;
}

bool Zombie::DropTable(int r)
{
	//For now, it will always return true so it will always drop an item
	//But if we want chances, then we'd uncomment the stuff.
	if (r < 39)
	return true;
	else
		return false;
}
