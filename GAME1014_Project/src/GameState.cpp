// Begin GameState
#include <ctime>
#include <cstdlib>

#include "GameState.h"

#include "EndState.h"
#include "PauseState.h"
#include "Slime.h"

#include "SoundManager.h"
GameState::GameState() {}

// State function

void GameState::Enter()
{
	int w, h;

	SDL_QueryTexture(TEMA::GetTexture("Background_1"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("Background", new Background({ 0,0,static_cast<int>(w),static_cast<int>(h) }, { 0,0, static_cast<float>(w) * 5, static_cast<float>(h) * 5 }, TEMA::GetTexture("Background_1")));

	//Register Textures
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_ALL_ANIMATION-Sheet.png", "Knight");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordskill.png", "SwordSkill1");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordAttack.png", "SwordAttack");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Slime.png", "Slime");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heart.png", "HeartBar");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heartempty.png", "EmptyHeart");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/spawn.png", "Spawn");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Sign_End.png", "End");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/on off.png", "On off");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Tileset.png", "tiles");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Potion.png", "Potion");

	
	m_levels.push_back(new TiledLevel(24, 200, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Mario_test.txt", "tiles"));
	m_levels.push_back(new TiledLevel(24, 48, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Level1.txt", "tiles"));

	//UI INTERFACE
	m_objects.emplace_back("Label3", new Label("Minecraft", 28, 645, "J", { 0,0,0,0 }));
	m_objects.emplace_back("Label4", new Label("Minecraft", 90, 645, "K", { 0,0,0,0 }));
	m_objects.emplace_back("HealthLabel", new Label("Minecraft", 20, 20, "Health", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel1", new Label("Minecraft", 800, 20, "Press Esc to exit game", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel2", new Label("Minecraft", 800, 40, "Press P to pause game", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel3", new Label("Minecraft", 800, 60, "Press Space to Jump", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel4", new Label("Minecraft", 800, 80, "Press J to Attack", { 0,0,0,0 }));
	m_objects.emplace_back("InstructionLabel5", new Label("Minecraft", 800, 100, "Press K to use Special", { 0,0,0,0 }));


	//UI Icons
	SDL_QueryTexture(TEMA::GetTexture("SwordAttack"), nullptr, nullptr, &w, &h);
	m_pSwordAttack = new SwordSkill({ 0,0,w,h }, { 10,595, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("SwordAttack"));
	m_UIObject.emplace_back("SwordAttack", m_pSwordAttack);

	SDL_QueryTexture(TEMA::GetTexture("SwordSkill1"), nullptr, nullptr, &w, &h);
	m_pSwordSkill1 = new SwordSkill({ 0,0,w,h }, { 70,595, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("SwordSkill1"));
	m_UIObject.emplace_back("SwordSkill1", m_pSwordSkill1);


	//First Level
	m_currLevel = 0;
	m_objects.emplace_back("level", m_levels[0]);

	m_spawn = dynamic_cast<TiledLevel*>(FindObject("level"))->GetStartingTile();
	SDL_FRect* s = m_spawn->GetDst();
	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &w, &h);

	m_objects.emplace_back("Player", new PlatformPlayer({ 0, 0, 77,h }, { s->x, s->y, static_cast<float>(77),static_cast<float>(h) }, TEMA::GetTexture("Knight")));


	//Slimes create
	SDL_QueryTexture(TEMA::GetTexture("Slime"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("aaa", new Slime({ 0, 0, 35, 29 }, { s->x + 32*6, s->y - 32*6, static_cast<float>(35), static_cast<float>(29) }, TEMA::GetTexture("Slime")));
	m_slimes.emplace_back(dynamic_cast<Slime*>(FindObject("aaa")));
	m_objects.emplace_back("penIsland", new Slime({ 0, 0, 35, 29 }, { s->x + 32 * 7, s->y - 32 * 6, static_cast<float>(35), static_cast<float>(29) }, TEMA::GetTexture("Slime")));
	m_slimes.emplace_back(dynamic_cast<Slime*>(FindObject("penIsland")));
	//SDL_QueryTexture(TEMA::GetTexture("Spawn"), nullptr, nullptr, &w, &h);
	//m_objects.emplace_back("Spawn", new ItemObject({ 0,0,w,h }, { s->x,s->y, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("Spawn")));
	
	SDL_FRect* r = dynamic_cast<TiledLevel*>(FindObject("level"))->GetEndTile()->GetDst();
	
	//SDL_QueryTexture(TEMA::GetTexture("End"), nullptr, nullptr, &w, &h);
	//m_objects.emplace_back("Trigger", new ItemObject({ 0,0,w,h }, { r->x,r->y, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("End")));
	
	SDL_QueryTexture(TEMA::GetTexture("HeartBar"), nullptr, nullptr, &w, &h);
	for(auto i = 0; i < dynamic_cast<PlatformPlayer*>(FindObject("Player"))->GetHeath(); i++)
	{
		auto* he = new Heart({ 0,0,w,h }, { static_cast<float>(10 + 30 * i), 50.0f, static_cast<float>(w),static_cast<float>(h) });
		Hearts.push_back(he);
		m_UIObject.emplace_back("HeartBar" + i, he);
	}




	std::cout << "Entering GameState..." << std::endl;


	//Load and play the game music
	SoundManager::Load("Aud/TownTheme.mp3", "gameLevel1", SOUND_MUSIC);
	SoundManager::PlayMusic("gameLevel1", -1);
	//SoundManager::SetMusicVolume(16);
}

void GameState::Update()
{
	//Random seed generation here
	srand((unsigned) time(NULL));

	MoveCamTo(FindObject("Player"));
	for (auto& m_object : m_objects)
		m_object.second->Update();
	CollisionCheck();
	
	if (EVMA::KeyPressed(SDL_SCANCODE_V))
	{
		//STMA::PushState(new PauseState());
		m_currLevel++;
		if (m_currLevel > m_levels.size() - 1)
			STMA::ChangeState(new TitleState());
		else
			ChangeLevel(m_currLevel);
	}
	
	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState());
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

	m_slimes.clear();
	m_slimes.shrink_to_fit();
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
	SDL_FRect* p = pp->GetBoundingBox();
	SDL_FRect* attackbox = pp->GetAttackHitBox();
	
	for (auto i : dynamic_cast<TiledLevel*>(FindObject("level"))->GetVisibleTile())
	{
		auto t = i->GetDst();
		if (COMA::AABBCheck(*p, *t)) // Collision check between player rect and tile rect.
		{
			if (i->GetTag() == OBSTACLE)
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
				else if (p->x - pp->GetVelX() + 3 >= t->x + t->w)
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
				}
			}
			else if (i->GetTag() == CHECKPOINT)
			{
				i->Activate();
				m_spawn = i;
			}
		}
		for (auto slime : m_slimes)
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
	for (auto i = 0; i < m_slimes.size(); i++)
	{
		SDL_FRect* s = m_slimes[i]->GetDst();
		if (COMA::AABBCheck(*s, *p))
		{
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
			m_slimes[i]->LoseHealth();
			if (m_slimes[i]->GetHeath() == 0)
			{
				if (m_slimes[i]->dropTable(rand() % 100) == true)
				{
					m_objects.emplace_back("Potion", new Potion({ 0, 0, 32, 32 }, { m_slimes[i]->GetDst()->x, m_slimes[i]->GetDst()->y, static_cast<float>(32), static_cast<float>(32) }, TEMA::GetTexture("Slime")));
					m_potions.emplace_back(dynamic_cast<Potion*>(FindObject("Potion")));
				}
				m_slimes.erase(m_slimes.begin() + i);
				m_slimes.shrink_to_fit();
			}
			cout << "Sword hits slimes" << endl;
		}
	}

	for (auto i = 0; i < m_potions.size(); i++)
	{
		SDL_FRect* ip = m_potions[i]->GetDst();
		if (COMA::AABBCheck(*ip, *p))
		{
			pp->SetHeath(pp->GetHeath() + 1);
			for (auto i2 = Hearts.size() - 1; i2 > 0; --i2)
			{
				if (Hearts[i2]->GetEmpty())
				{
					Hearts[i2]->SetEmpty(false);
					break;
				}
			}
			cout << "Collect potion" << endl;
			m_potions.erase(m_potions.begin() + i);
			m_potions.shrink_to_fit();
		}
	}
	
	// This has to be at the end because of ChangeState
	if (p->y >= HEIGHT + p->h || EVMA::KeyPressed(SDL_SCANCODE_MINUS))
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

	if (dynamic_cast<GameState*>(STMA::GetStates().back()) != nullptr)
	{
		if (m_currLevel > m_levels.size() -1)
			STMA::ChangeState(new TitleState());
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
	o->GetDst()->x += camOffset;
	//FindObject("Player")->GetDst()->x += camOffset;
	FindObject("aaa")->GetDst()->x += camOffset;
	FindObject("penIsland")->GetDst()->x += camOffset;
	if (m_potions.size() > 0)
	{
		for (int i = 0; i < m_potions.size(); i++)
		{
			FindObject("Potion")->GetDst()->x += camOffset;
		}
	}
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
	//auto sp = FindObject("Spawn");
	//sp->GetDst()->x = s->x;
	//sp->GetDst()->y = s->y;

	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	pp->StopX();
	pp->StopY();
	pp->SetX(s->x);
	pp->SetY(s->y);
	MoveCamTo(pp);
	
	//SDL_FRect* r = dynamic_cast<TiledLevel*>(FindObject("level"))->GetEndTile()->GetDst();
	//auto t = FindObject("Trigger");
	//t->GetDst()->x = r->x;
	//t->GetDst()->y = r->y;
	
	//m_objects.emplace_back("level", m_levels[1]);
	
}