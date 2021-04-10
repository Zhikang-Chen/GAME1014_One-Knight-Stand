// Begin GameState
#include <ctime>
#include "EventManager.h"
#include "SaveManager.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"

GameState::GameState() {}

// State function

void GameState::Enter()
{


	int w, h;
	auto save = SAMA::GetSave();
	
	SDL_QueryTexture(TEMA::GetTexture("Background_1"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("Background", new Background({ 0,0,static_cast<int>(w),static_cast<int>(h) }, { 0,0, static_cast<float>(w) * 5, static_cast<float>(h) * 5 }, TEMA::GetTexture("Background_1")));

	//Register Textures
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight Edited.png", "Knight");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/skills-ui.png", "SkillsUI");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill1.png", "SwordSkill1");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill2.png", "SwordSkill2");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill1CD.png", "SwordSkill1CD");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill2CD.png", "SwordSkill2CD");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordAttack.png", "SwordAttack");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Slime.png", "Slime");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Zombie.png", "Zombie");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/dagger.png", "Project");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Potion.png", "Potion");


	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heart.png", "HeartBar");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heartempty.png", "EmptyHeart");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/spawn.png", "Spawn");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Sign_End.png", "End");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/on off.png", "On off");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Tileset.png", "tiles");
	//TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Tiles.png", "tiles2");
	
	m_levels.push_back(new TiledLevel(24, 200, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Mario_test.txt", "tiles"));
	m_levels.push_back(new TiledLevel(24, 247, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Level2.txt", "tiles"));
	m_levels.push_back(new TiledLevel(24, 284, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Level3.txt", "tiles"));
	m_levels.push_back(new TiledLevel(24, 283, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Level3.txt", "tiles"));
	m_levels.push_back(new TiledLevel(24, 48, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Level1.txt", "tiles"));

	//UI INTERFACE
	m_UIObject.emplace_back("Label3", new Label("Minecraft", 56, 150, "J", { 0,0,0,0 }));
	m_UIObject.emplace_back("Label4", new Label("Minecraft", 110, 150, "K", { 0,0,0,0 }));
	m_UIObject.emplace_back("Label5", new Label("Minecraft", 160, 150, "L", { 0,0,0,0 }));
	m_UIObject.emplace_back("HealthLabel", new Label("Minecraft", 400, 20, "Sponsored by: NornVPN", { 0,0,0,0 }));
	m_UIObject.emplace_back("InstructionLabel1", new Label("Minecraft", 790, 20, "Press Esc to exit game", { 0,0,0,0 }));
	m_UIObject.emplace_back("InstructionLabel2", new Label("Minecraft", 790, 40, "Press P to pause game", { 0,0,0,0 }));
	m_UIObject.emplace_back("InstructionLabel3", new Label("Minecraft", 790, 60, "Press Space to Jump", { 0,0,0,0 }));
	m_UIObject.emplace_back("InstructionLabel4", new Label("Minecraft", 790, 80, "Press J to Attack", { 0,0,0,0 }));
	m_UIObject.emplace_back("InstructionLabel5", new Label("Minecraft", 790, 100, "Press K to use Special 1", { 0,0,0,0 }));
	m_UIObject.emplace_back("InstructionLabel6", new Label("Minecraft", 790, 120, "Press L to use Special 2", { 0,0,0,0 }));

	//UI Icons
	SDL_QueryTexture(TEMA::GetTexture("SkillsUI"), nullptr, nullptr, &w, &h);
	m_pSkillsUI = new SwordSkill({ 0,0,w,h }, { 10,5, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("SkillsUI"));
	m_UIObject.emplace_back("SkillsUI", m_pSkillsUI);

	SDL_QueryTexture(TEMA::GetTexture("HealthUI"), nullptr, nullptr, &w, &h);
	m_pHealthUI = new SwordSkill({ 0,0,w,h }, { 10,200, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("HealthUI"));
	m_UIObject.emplace_back("HealthUI", m_pHealthUI);

	SDL_QueryTexture(TEMA::GetTexture("SwordAttack"), nullptr, nullptr, &w, &h);
	m_pSwordAttack = new SwordSkill({ 0,0,w,h }, { 50,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordAttack"));
	m_UIObject.emplace_back("SwordAttack", m_pSwordAttack);

	SDL_QueryTexture(TEMA::GetTexture("SwordSkill1"), nullptr, nullptr, &w, &h);
	m_pSwordSkill1 = new SwordSkill({ 0,0,w,h }, { 100,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordSkill1"));
	m_UIObject.emplace_back("SwordSkill1", m_pSwordSkill1);

	
	
	SDL_QueryTexture(TEMA::GetTexture("SwordSkill2"), nullptr, nullptr, &w, &h);
	m_pSwordSkill2 = new SwordSkill({ 0,0,w,h }, { 150,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordSkill2"));
	m_UIObject.emplace_back("SwordSkill2", m_pSwordSkill2);
	
	//First Level
	m_currLevel = save->m_currLevel;
	m_objects.emplace_back("level", m_levels[m_currLevel]);

	m_currCheckPoint = save->m_checkpoint;
	
	m_spawn = dynamic_cast<TiledLevel*>(FindObject("level"))->GetCheckPoint()[m_currCheckPoint];
	SDL_FRect* s = m_spawn->GetDst();
	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &w, &h);

	auto Pp = new PlatformPlayer({ 0, 0, 77,h/5 }, { s->x, s->y, static_cast<float>(77),static_cast<float>(h)/5 }, TEMA::GetTexture("Knight"));
	m_objects.emplace_back("Player", Pp);
	Pp->SetHeath(save->m_currHealth);
	Pp->SetMaxHealth(save->m_maxHealth);
	
	SDL_QueryTexture(TEMA::GetTexture("HeartBar"), nullptr, nullptr, &w, &h);
	for(auto i = 0; i < Pp->GetMaxHealth(); i++)
	{
		auto* he = new Heart({ 0,0,w,h }, { static_cast<float>(100 + 25 * i), 40.0f, static_cast<float>(w),static_cast<float>(h) });
		if (Pp->GetHeath() <= i )
			he->SetEmpty(true);
		Hearts.push_back(he);
		m_UIObject.emplace_back("HeartBar" + i, he);
	}


	//Load and play the game music
	SoundManager::Load("Aud/TownTheme.mp3", "gameLevel1", SOUND_MUSIC);
	SoundManager::PlayMusic("gameLevel1", -1);
	SoundManager::Load("Aud/healing.wav", "heal", SOUND_SFX);
	SoundManager::Load("Aud/slime_movement.wav", "bounce", SOUND_SFX);
	SoundManager::Load("Aud/ouch.wav", "hit", SOUND_SFX);
	SoundManager::Load("Aud/bonk.wav", "bonk", SOUND_SFX);
	SoundManager::Load("Aud/zombie.wav", "zombie", SOUND_SFX);
	SoundManager::Load("Aud/checkpoint.wav", "check", SOUND_SFX);
	
	//SoundManager::SetMusicVolume(16);
	std::cout << "Entering GameState..." << std::endl;
}

void GameState::Update()
{
	srand((unsigned)time(NULL));
	MoveCamTo(FindObject("Player"));
	for (auto& m_object : m_objects)
		m_object.second->Update();
	CollisionCheck();
	
	if (EVMA::KeyPressed(SDL_SCANCODE_V))
	{
		//STMA::PushState(new PauseState());
		m_currLevel++;
		if (m_currLevel < m_levels.size())
			ChangeLevel(m_currLevel);
		else
			STMA::ChangeState(new GameClearState());
			return;
	}
	
	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState());
	}

	int w, h;

	if (dynamic_cast<PlatformPlayer*>(FindObject("Player"))->getSkill1CD() == true)
	{
		SDL_QueryTexture(TEMA::GetTexture("SwordSkill1CD"), nullptr, nullptr, &w, &h);
		m_pSwordSkill1CD = new SwordSkill({ 0,0,w,h }, { 100,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordSkill1CD"));
		m_UIObject.emplace_back("SwordSkill1CD", m_pSwordSkill1CD);
	}
	else
	{
		SDL_QueryTexture(TEMA::GetTexture("SwordSkill1"), nullptr, nullptr, &w, &h);
		m_pSwordSkill1 = new SwordSkill({ 0,0,w,h }, { 100,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordSkill1"));
		m_UIObject.emplace_back("SwordSkill1", m_pSwordSkill1);
		dynamic_cast<PlatformPlayer*>(FindObject("Player"))->setSkill1CD(false);
	}

	if (dynamic_cast<PlatformPlayer*>(FindObject("Player"))->getSkill2CD() == true)
	{
		SDL_QueryTexture(TEMA::GetTexture("SwordSkill2CD"), nullptr, nullptr, &w, &h);
		m_pSwordSkill2CD = new SwordSkill({ 0,0,w,h }, { 150,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordSkill2CD"));
		m_UIObject.emplace_back("SwordSkill2CD", m_pSwordSkill2CD);
	}
	else
	{
		SDL_QueryTexture(TEMA::GetTexture("SwordSkill2"), nullptr, nullptr, &w, &h);
		m_pSwordSkill2 = new SwordSkill({ 0,0,w,h }, { 150,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordSkill2"));
		m_UIObject.emplace_back("SwordSkill2", m_pSwordSkill2);
		dynamic_cast<PlatformPlayer*>(FindObject("Player"))->setSkill2CD(false);
	}
	
}

void GameState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	
	for (auto& m_object : m_objects)
		m_object.second->Render();

	for (auto& i : m_UIObject)
		i.second->Render();


	if (dynamic_cast<GameState*>(STMA::GetStates().back()) != nullptr) // Check to see if current state is of type GameState
		State::Render();
}

void GameState::Exit()
{
	//SAMA::OverwriteSave();
	
	for (auto& m_object : m_objects)
	{
		delete m_object.second;
		m_object.second = nullptr;
	}
	m_objects.clear();

	for (auto& UI : m_UIObject)
	{
		delete UI.second;
		UI.second = nullptr;
	}


	
	m_UIObject.clear();
	Hearts.clear();
	std::cout << "Exiting GameState..." << std::endl;
}

void GameState::Resume()
{
	SoundManager::PlayMusic("gameLevel1", -1);
	cout << "Resuming GameState" << endl;
}

// GameState function
void GameState::CollisionCheck()
{
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	SDL_FRect* p = pp->GetDst();
	SDL_FRect* attackbox = pp->GetAttackHitBox();


	for (auto i : m_levels[m_currLevel]->GetRenderTile())
	{
		auto t = i->GetDst();
		if (COMA::AABBCheck(*p, *t)) // Collision check between player rect and tile rect.
		{
			if (i->GetTag() == OBSTACLE)
			{
				if (p->y + p->h - pp->GetVelY() <= t->y)
				{ // Colliding with top side of tile.
					pp->StopY();
					pp->SetY(t->y - p->h);
					pp->SetGrounded(true);
				}
				else if (p->y - pp->GetVelY() >= (t->y + t->h))
				{ // Colliding with bottom side of tile.
					pp->StopY();
					pp->SetY(t->y + t->h);
				}
				else if (p->x - pp->GetVelX() <= t->x - t->w)
				{ // Colliding with left side of tile.
					pp->StopX();
					pp->SetX(t->x - p->w);
				}
				else if (p->x - pp->GetVelX() >= t->x + t->w)
				{ // Colliding with right side of tile.
					pp->StopX();
					pp->SetX(t->x + t->w);
				}
			}
			else if (i->GetTag() == PLATFORM)
			{
				if (!EVMA::KeyHeld(SDL_SCANCODE_S))
				{
					if (p->y + p->h - pp->GetVelY() <= t->y)
					{ // Colliding with top side of tile.
						pp->StopY();
						pp->SetY(t->y - p->h);
						pp->SetGrounded(true);
					}
				}
			}
			else if (i->GetTag() == END)
			{
				if (EVMA::KeyPressed(SDL_SCANCODE_E))
				{
					//STMA::PushState(new PauseState());
					m_currLevel++;
					if (m_currLevel < m_levels.size())
						ChangeLevel(m_currLevel);
					else
					{
						STMA::ChangeState(new GameClearState());
						return;
					}
				}
			}
			else if (i->GetTag() == CHECKPOINT)
			{
				
				
				for(unsigned int i2 = 0 ; i2 < m_levels[m_currLevel]->GetCheckPoint().size() ; i2++)
				{
					
				
					if (m_levels[m_currLevel]->GetCheckPoint()[i2] == i)
					{
						//Play the checkpoint sound once after touching the flag. Shouldnt play again if touching it twice
						m_currCheckPoint = i2;

				
				
						SoundManager::PlaySound("check", 0, 4);
						

						
					}
					
				
								
				}
				i->Activate();
				m_spawn = i;

				
			}
	

			
		}
		for (auto enemy : m_levels[m_currLevel]->GetEnemy())
		{
			auto e = enemy->GetDst();
			if (p->x < e->x)
			{
				enemy->faceDir(false);
			}
			else
			{
				enemy->faceDir(true);
			}

			if (COMA::AABBCheck(*e, *t)) // Collision check between player rect and tile rect.
			{
				if ((e->y + e->h) - enemy->GetVelY() <= t->y)
				{ // Colliding with top side of tile.
					enemy->StopY();
					enemy->SetY(t->y - e->h);
					enemy->SetGrounded(true);
				}
				else if (e->y - enemy->GetVelY() >= (t->y + t->h))
				{ // Colliding with bottom side of tile.
					enemy->StopY();
					enemy->SetY(t->y + t->h);
				}
				else if (e->x - enemy->GetVelX() <= t->x - t->w)
				{ // Colliding with left side of tile.
					enemy->StopX();
					enemy->SetX(t->x - e->w);
				}
				else if (e->x - enemy->GetVelX() >= t->x + t->w)
				{ // Colliding with right side of tile.
					enemy->StopX();
					enemy->SetX(t->x + t->w);
				}
			}
		}
	}
	
	//Player attack and enemies collision
	auto &enemies = m_levels[m_currLevel]->GetEnemy();
	for (auto i = 0; i < enemies.size(); i++)
	{
		SDL_FRect* s = enemies[i]->GetDst();
		if (COMA::AABBCheck(*s, *p))
		{
			SoundManager::PlaySound("hit", 0, 1);
			pp->SetHeath(pp->GetHeath() - 1);

			for (auto i2 = Hearts.size() - 1; i2 > 0; --i2)
			{
				if (!Hearts[i2]->GetEmpty())
				{
					Hearts[i2]->SetEmpty(true);
					break;
				}
			}
			SDL_FRect* s = m_spawn->GetDst();
			pp->StopX();
			pp->StopY();
			pp->SetX(s->x);
			pp->SetY(s->y);
			MoveCamTo(pp);
		}

		//Attack Collision with Enemies
		if (COMA::AABBCheck(*attackbox, *s))
		{
			switch (pp->GetCurrentAttack())
			{
			case AttackType::NORMAL:
				cout << "hit" << endl;
				enemies[i]->LoseHealth();
				break;
			case AttackType::ICE:
				enemies[i]->addEffect(new Bleed(61));
				enemies[i]->addEffect(new Freeze(120));
				break;
			case AttackType::BONK:
				enemies[i]->addEffect(new Stun(300));
				SoundManager::PlaySound("bonk", 0, 0);
				break;
			case AttackType::BLEED:
				enemies[i]->addEffect(new Bleed(300));
				break;
			}
		}
		
		if (enemies[i]->GetHeath() <= 0)
		{
		
			int randomDrop = rand() % 100;
			if (enemies[i]->DropTable(randomDrop) == true)
			{
				m_levels[m_currLevel]->AddPotion(new HealthPotion({ 0, 0, 32, 32 }, { enemies[i]->GetDst()->x, enemies[i]->GetDst()->y, static_cast<float>(32), static_cast<float>(32) }));
			}
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			enemies.shrink_to_fit();
		}
	}

	//Player and potion collision
	auto &idk = m_levels[m_currLevel]->GetPotion();
	for (unsigned i = 0; i < idk.size(); i++)
	{
		SDL_FRect* po = idk[i]->GetDst();
		if (COMA::AABBCheck(*p, *po))
		{
			SoundManager::PlaySound("heal", 0, 2);
			if (pp->GetHeath() < 10)
			{
				
				pp->SetHeath(pp->GetHeath() + 1);
			}
			delete idk[i];
			idk.erase(idk.begin() + i);
			idk.shrink_to_fit();
			
			for (auto i2 = 0; i2 < Hearts.size(); i2++)
			{
				if (Hearts[i2]->GetEmpty())
				{
					Hearts[i2]->SetEmpty(false);
					break;
				}
			}
		}
	}

	// This has to be at the end because of ChangeState
	if (p->y >= HEIGHT + p->h)
	{
		pp->SetHeath(pp->GetHeath() - 1);
		for (auto i = Hearts.size() - 1; i > 0; --i)
		{
			if (!Hearts[i]->GetEmpty())
			{
				Hearts[i]->SetEmpty(true);
				break;
			}
		}
		SDL_FRect* s = m_spawn->GetDst();
		pp->StopX();
		pp->StopY();
		pp->SetX(s->x);
		pp->SetY(s->y);
		MoveCamTo(pp);
	}

	if (pp->GetHeath() == 0)
	{
		STMA::ChangeState(new EndState());
	}
}

void GameState::MoveCamTo(GameObject* o)
{
	auto camOffset = (WIDTH / 2) - o->GetDst()->x;
	
	for(auto i : m_levels[m_currLevel]->GetVisibleTile())
	{
		SDL_FRect* t = i->GetDst();
		t->x += camOffset;
	}
	
	for(auto i : m_levels[m_currLevel]->GetEnemy())
	{
		i->GetDst()->x += camOffset;
	}
	for (unsigned i = 0; i < m_levels[m_currLevel]->GetPotion().size(); i++)
	{
		m_levels[m_currLevel]->GetPotion()[i]->GetDst()->x += camOffset;
	}
	o->GetDst()->x += camOffset;
}

void GameState::ChangeLevel(unsigned int level)
{
	for (auto& m_object : m_objects)
	{
		if (m_object.first == "level")
		{
			if (m_object.second == m_levels[level])
				return;

			//delete m_object.second;
			m_object.second = m_levels[level];
			//m_object.second = nullptr;
		}
	}
	m_currCheckPoint = 0;
	m_spawn = dynamic_cast<TiledLevel*>(FindObject("level"))->GetStartingTile();
	SDL_FRect* s = m_spawn->GetDst();
	
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	pp->StopX();
	pp->StopY();
	pp->SetX(s->x);
	pp->SetY(s->y);
	MoveCamTo(pp);
	STMA::PushState(new LoadState());
}

unsigned int GameState::GetLevel() const { return m_currLevel;}

unsigned int GameState::GetCheckPoint() const { return m_currCheckPoint; }
