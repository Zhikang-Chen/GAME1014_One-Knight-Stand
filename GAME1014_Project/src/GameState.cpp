// Begin GameState
#include "GameState.h"

#include "EndState.h"
#include "PauseState.h"
#include "TiledLevel.h"

GameState::GameState() {}

void GameState::Enter()
{
	int w, h;

	SDL_QueryTexture(TEMA::GetTexture("Background_1"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("Background", new Background({ 0,0,(int)w,(int)h }, { 0,0, (float)w * 5, (float)h * 5 }, TEMA::GetTexture("Background_1")));

	//Ui test and i am not sorry for typing those
	//Remove when use
	m_objects.emplace_back("Label", new Label("Minecraft", WIDTH / 2, HEIGHT / 2 + 20, "UWU? What's dis", { 0,0,0,0 }));
	m_objects.emplace_back("Label2", new Label("Minecraft", WIDTH / 2, HEIGHT / 2 + 40, "I am your cute UI GF", { 0,0,0,0 }));
	m_objects.emplace_back("Label3", new Label("Minecraft", 28, 645, "Q", { 0,0,0,0 }));
	m_objects.emplace_back("Label4", new Label("Minecraft", 148, 645, "J", { 0,0,0,0 }));
	m_objects.emplace_back("Label6", new Label("Minecraft", 10, 45, "Health: ", { 0,0,0,0 }));
	//TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_RUNNING_AND_IDLE.png", "Knight");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_ALL_ANIMATION-Sheet.png", "Knight");
<<<<<<< Updated upstream
=======
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/skills-ui.png", "SkillsUI");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill1.png", "SwordSkill1");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill2.png", "SwordSkill2");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill1CD.png", "SwordSkill1CD");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordSkill2CD.png", "SwordSkill2CD");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordAttack.png", "SwordAttack");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Slime.png", "Slime");
>>>>>>> Stashed changes

	
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/sword.png", "IDK"); 
	//TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_Attacking.png", "Knight-Attack");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordskill.png", "SwordSkill1");


	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heart.png", "HeartBar");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heart.png", "HeartBar1");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heartempty.png", "EmptyHeart");
	
	//SDL_Rect src{ 20,20,100,100 }, dir{0,0,100,100};

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Tileset.png", "tiles");
	m_objects.emplace_back("level", new TiledLevel(24, 249, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.txt", "../GAME1017_Template_W01/Dat/Mario_test.txt", "tiles"));
	
	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &w, &h);
	//m_player = new PlatformPlayer({ 0, 0, width / 14,height }, { 0,0, float(width / 14),float(height) }, TEMA::GetTexture("Knight"));
	m_objects.emplace_back("Player", new PlatformPlayer({ 0, 0, 77,h }, { WIDTH/2,0, static_cast<float>(77),static_cast<float>(h) }, TEMA::GetTexture("Knight")));

<<<<<<< Updated upstream
	SDL_QueryTexture(TEMA::GetTexture("IDK"), nullptr, nullptr, &w, &h);
	m_pWeapon = new Sword({ 0,0,w,h }, { 0,0, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("IDK"));

	//Use to test item class remove when done
	m_pWeapon->SetTarget(FindObject("Player")->GetDst());
	m_pWeapon->SetEnable(false);
	m_objects.emplace_back("sword", m_pWeapon);

	SDL_QueryTexture(TEMA::GetTexture("IDK"), nullptr, nullptr, &w, &h);
	AnItem = new ItemObject({ 0,0,w,h }, { 32*5,650, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("IDK"));
	m_objects.emplace_back("Weapon", AnItem);

	SDL_QueryTexture(TEMA::GetTexture("HeartBar"), nullptr, nullptr, &w, &h);
	m_pHeartbar = new Heart({ 0,0 , w,h }, { 10,70, float(w),float(h) }, TEMA::GetTexture("HeartBar"));
	m_objects.emplace_back("HeartBar", m_pHeartbar);
	m_pFullHeart = new Heart({ 0,0 , w,h }, { 40,70, float(w),float(h) }, TEMA::GetTexture("HeartBar1"));
	m_objects.emplace_back("HeartBar1", m_pFullHeart);

	SDL_QueryTexture(TEMA::GetTexture("EmptyHeart"), nullptr, nullptr, &w, &h);
	m_pEmptyHeart = new Heart({ 0,0 , w,h }, { 70,70, float(w),float(h) }, TEMA::GetTexture("EmptyHeart"));
	m_objects.emplace_back("EmptyHeart", m_pEmptyHeart);

	SDL_QueryTexture(TEMA::GetTexture("SwordSkill1"), nullptr, nullptr, &w, &h);
	m_pSwordSkill1 = new SwordSkill({ 0,0,w,h }, { 10,595, float(w),float(h) }, TEMA::GetTexture("SwordSkill1"));
	m_objects.emplace_back("SwordSkill1", m_pSwordSkill1);
	
	std::cout << "Entering GameState..." << std::endl;
}
=======
	//UI INTERFACE
	m_objects.emplace_back("Label3", new Label("Minecraft", 56, 150, "J", { 0,0,0,0 }));
	m_objects.emplace_back("Label4", new Label("Minecraft", 110, 150, "K", { 0,0,0,0 }));
	m_objects.emplace_back("Label5", new Label("Minecraft", 160, 150, "L", { 0,0,0,0 }));
	m_objects.emplace_back("HealthLabel", new Label("Minecraft", 400, 20, "Sponsored by: NornVPN", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel1", new Label("Minecraft", 790, 20, "Press Esc to exit game", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel2", new Label("Minecraft", 790, 40, "Press P to pause game", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel3", new Label("Minecraft", 790, 60, "Press Space to Jump", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel4", new Label("Minecraft", 790, 80, "Press J to Attack", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel5", new Label("Minecraft", 790, 100, "Press K to use Special 1", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel6", new Label("Minecraft", 790, 120, "Press L to use Special 2", { 0,0,0,0 }));

	//UI Icons
	SDL_QueryTexture(TEMA::GetTexture("SkillsUI"), nullptr, nullptr, &w, &h);
	m_pSkillsUI = new SwordSkill({ 0,0,w,h }, { 10,5, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("SkillsUI"));
	m_UIObject.emplace_back("SkillsUI", m_pSkillsUI);

	SDL_QueryTexture(TEMA::GetTexture("HealthUI"), nullptr, nullptr, &w, &h);
	m_pHealthUI = new SwordSkill({ 0,0,w,h }, { 10,200, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("HealthUI"));
	m_UIObject.emplace_back("HealthUI", m_pHealthUI);
	
	SDL_QueryTexture(TEMA::GetTexture("SwordAttack"), nullptr, nullptr, &w, &h);
	m_pSwordAttack = new SwordSkill({ 0,0,w,h }, { 50,109, static_cast<float>(w-16),static_cast<float>(h-16) }, TEMA::GetTexture("SwordAttack"));
	m_UIObject.emplace_back("SwordAttack", m_pSwordAttack);

	SDL_QueryTexture(TEMA::GetTexture("SwordSkill1"), nullptr, nullptr, &w, &h);
	m_pSwordSkill1 = new SwordSkill({ 0,0,w,h }, { 100,109, static_cast<float>(w-16),static_cast<float>(h-16) }, TEMA::GetTexture("SwordSkill1"));
	m_UIObject.emplace_back("SwordSkill1", m_pSwordSkill1);

	SDL_QueryTexture(TEMA::GetTexture("SwordSkill2"), nullptr, nullptr, &w, &h);
	m_pSwordSkill2 = new SwordSkill({ 0,0,w,h }, { 150,109, static_cast<float>(w - 16),static_cast<float>(h - 16) }, TEMA::GetTexture("SwordSkill2"));
	m_UIObject.emplace_back("SwordSkill2", m_pSwordSkill2);
	

	m_currLevel = 0;
	m_objects.emplace_back("level", m_levels[0]);
>>>>>>> Stashed changes


//Check collision between platforms and the player
void GameState::CollisionCheck()
{
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	SDL_FRect* p = pp->GetDst();
	for (int i = 0; i < dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles().size(); i++)
	{
		SDL_FRect* t = dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles()[i]->GetDst();
		if (COMA::AABBCheck(*p, *t)) // Collision check between player rect and tile rect.
		{
			if ((p->y + p->h) - pp->GetVelY() <= t->y)
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
			else if (p->x  - pp->GetVelX() >= t->x + t->w)
			{ // Colliding with right side of tile.
				pp->StopX();
				pp->SetX(t->x + t->w);
			}
		}
	}
	
	// Use to test 
	if (COMA::AABBCheck(*p, *AnItem->GetDst()))
	{
		if(EVMA::KeyPressed(SDL_SCANCODE_E))
		{
			AnItem->Activate();
			m_pWeapon->SetEnable(true);
		}
	}

	//This has to be at the end
	if (p->y >= HEIGHT + p->h)
	{
		STMA::ChangeState(new EndState());
	}
	
}

void GameState::UpdateCam()
{
	float camspeed = 0.0;
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	if (pp->GetDst()->x >= (WIDTH / 2) + 64)
	{
<<<<<<< Updated upstream
		//std::cout << "Right" << endl;
		//m_camOffset = (WIDTH / 2) - (m_player->GetDst()->x - (m_player->GetDst()->w / 2));
		//cout << m_camOffset << endl;
		//camspeed = -6.0f;
		//
		//if (pp->GetDst()->x >= (WIDTH / 2) + 128)
			camspeed = pp->GetVelX() * -1;
	}
	else if (pp->GetDst()->x <= (WIDTH / 2) - 64)
	{
		//std::cout << "Left" << endl;
		//m_camOffset = (WIDTH / 2) - (m_player->GetDst()->x + ( m_player->GetDst()->w / 2));
		//cout << m_camOffset << endl;
		//camspeed = 6.0f;
		//
		//if (pp->GetDst()->x <= (WIDTH / 2) - 128)
			camspeed = pp->GetVelX() * -1;
=======
		auto* he = new Heart({ 0,0,w,h }, { static_cast<float>(100 + 25 * i), 40.0f, static_cast<float>(w),static_cast<float>(h) });
		Hearts.push_back(he);
		m_UIObject.emplace_back("HeartBar" + i, he);
>>>>>>> Stashed changes
	}

	for (int i = 0; i < dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles().size(); i++)
	{
		SDL_FRect* t = dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles()[i]->GetDst();
		t->x += camspeed;
	}

	//for (auto& m_object : m_objects)
	//	m_object.second->GetDst()->x += camspeed;
	//FindObject("Label4")->GetDst()->x += camspeed;
	//FindObject("Label5")->GetDst()->x += camspeed;
	FindObject("Player")->GetDst()->x += camspeed;
	FindObject("Weapon")->GetDst()->x += camspeed;

}

void GameState::Update()
{
	UpdateCam();
	for (auto& m_object : m_objects)
		m_object.second->Update();
	CollisionCheck();
	if(EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState());
	}
}

void GameState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (auto& i : m_UIObject)
		i.second->Render();
	
	for (auto& m_object : m_objects)
		m_object.second->Render();
	
	if (dynamic_cast<GameState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
		State::Render();
	
}

void GameState::Exit()
{
	for (auto& m_object : m_objects)
	{
		delete m_object.second;
		m_object.second = nullptr;
	}
	m_objects.clear();
	
	std::cout << "Exiting GameState..." << std::endl;
}

void GameState::Resume()
{
	cout << "Resuming GameState" << endl;
}
<<<<<<< Updated upstream
// End GameState
=======

// GameState function
void GameState::CollisionCheck()
{
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	SDL_FRect* p = pp->GetDst();
	SDL_FRect* attackbox = pp->GetAttackHitBox();
	SDL_FRect* Sattackbox = pp->GetSAttackHitBox();

	for (auto i : dynamic_cast<TiledLevel*>(FindObject("level"))->GetVisibleTile())
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
				else if (p->x - pp->GetVelX()  >= t->x + t->w)
				{ // Colliding with right side of tile.
					pp->StopX();
					pp->SetX(t->x + t->w);
				}
			}
			else if(i->GetTag() == END)
			{
				if (EVMA::KeyPressed(SDL_SCANCODE_E))
				{
					//STMA::PushState(new PauseState());
					m_currLevel++;
					if (m_currLevel <= m_levels.size() - 1)
						ChangeLevel(m_currLevel);
					else
						STMA::ChangeState(new TitleState());
				}
			}
			else if (i->GetTag() == CHECKPOINT)
			{
				i->Activate();
				m_spawn = i;
			}
		}
		for (auto slime : dynamic_cast<TiledLevel*>(FindObject("level"))->GetEnemy())
		{
			auto e = slime->GetDst();
			if (p->x < e->x)
			{
				slime->faceDir(false);
			}
			else
			{
				slime->faceDir(true);
			}

			if (COMA::AABBCheck(*e, *t)) // Collision check between player rect and tile rect.
			{
				if ((e->y + e->h) - slime->GetVelY() <= t->y)
				{ // Colliding with top side of tile.
					slime->StopY();
					slime->SetY(t->y - e->h);
					slime->SetGrounded(true);
				}
				else if (e->y - slime->GetVelY() >= (t->y + t->h))
				{ // Colliding with bottom side of tile.
					slime->StopY();
					slime->SetY(t->y + t->h);
				}
				else if (e->x - slime->GetVelX() <= t->x - t->w)
				{ // Colliding with left side of tile.
					slime->StopX();
					slime->SetX(t->x - e->w);
				}
				else if (e->x - slime->GetVelX() >= t->x + t->w)
				{ // Colliding with right side of tile.
					slime->StopX();
					slime->SetX(t->x + t->w);
				}
			}

			
		}
	}

	// Heal the player
	// Remove at beta
	//if(EVMA::KeyPressed(SDL_SCANCODE_EQUALS) && pp->GetHeath() != pp->GetMaxHealth())
	//{
	//	pp->SetHeath(pp->GetHeath() + 1);
	//	for (auto i = 0; i < Hearts.size() ; ++i)
	//	{
	//		if (Hearts[i]->GetEmpty())
	//		{
	//			Hearts[i]->SetEmpty(false);
	//			break;
	//		}
	//	}
	//}
	//Player and slime collision
	auto &enemies = dynamic_cast<TiledLevel*>(FindObject("level"))->GetEnemy();
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
		//SDL_FRect* slimes = m_slimes[i]->GetDst();
		//Attack Collision with Enemies
		if (COMA::AABBCheck(*attackbox, *s))
		{
			enemies[i]->LoseHealth();
			if (enemies[i]->GetHeath() == 0)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				enemies.shrink_to_fit();
				SoundManager::PlaySound("bounce", 0, 3);
				//SoundManager::SetSoundVolume(15);
				
			}
			cout << "Sword hits slimes" << endl;
		}
		if (COMA::AABBCheck(*Sattackbox, *s))
		{
			enemies[i]->LoseHealth();
			if (enemies[i]->GetHeath() == 0)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				enemies.shrink_to_fit();
				SoundManager::PlaySound("bounce", 0, 3);
				//SoundManager::PlaySound("bounce", 0, 0);
				//SoundManager::SetSoundVolume(15);

			}
			cout << "Special hits slimes" << endl;
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
	
	for(auto i : dynamic_cast<TiledLevel*>(FindObject("level"))->GetAllTile())
	{
		for(auto i2 : i)
		{
			SDL_FRect* t = i2->GetDst();
			t->x += camOffset;
		}
	}
	for(auto i : dynamic_cast<TiledLevel*>(FindObject("level"))->GetEnemy())
	{
		i->GetDst()->x += camOffset;
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
	m_spawn = dynamic_cast<TiledLevel*>(FindObject("level"))->GetStartingTile();
	SDL_FRect* s = m_spawn->GetDst();
	
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	pp->StopX();
	pp->StopY();
	pp->SetX(s->x);
	pp->SetY(s->y);
	MoveCamTo(pp);
}
>>>>>>> Stashed changes
