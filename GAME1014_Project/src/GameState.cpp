// Begin GameState
#include "GameState.h"

#include "EndState.h"
#include "PauseState.h"
#include "TiledLevel.h"
#include "Slime.h"

#include "SoundManager.h"
GameState::GameState() {}

void GameState::Enter()
{
	int w, h;

	SDL_QueryTexture(TEMA::GetTexture("Background_1"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("Background", new Background({ 0,0,static_cast<int>(w),static_cast<int>(h) }, { 0,0, static_cast<float>(w) * 5, static_cast<float>(h) * 5 }, TEMA::GetTexture("Background_1")));

	//Ui test and i am not sorry for typing those
	//Remove when beta
	m_objects.emplace_back("Label", new Label("Minecraft", WIDTH / 2, HEIGHT / 2 + 20, "UWU? What's dis", { 0,0,0,0 }));
	m_objects.emplace_back("Label2", new Label("Minecraft", WIDTH / 2, HEIGHT / 2 + 40, "I am your cute UI GF", { 0,0,0,0 }));
	//m_objects.emplace_back("Label6", new Label("Minecraft", 10, 45, "Health: 5/5", { 0,0,0,0 }));
	//TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_RUNNING_AND_IDLE.png", "Knight");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_ALL_ANIMATION-Sheet.png", "Knight");

	//TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_Attacking.png", "Knight-Attack");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/swordskill.png", "SwordSkill1");

	//Slime register texture
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Slime.png", "Slime");


	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heart.png", "HeartBar");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heartempty.png", "EmptyHeart");
	
	//SDL_Rect src{ 20,20,100,100 }, dir{0,0,100,100};

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Tileset.png", "tiles");
	m_objects.emplace_back("level", new TiledLevel(24, 200, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.xml", "../GAME1017_Template_W01/Dat/Mario_test.txt", "tiles"));
	
	SDL_FRect* s = dynamic_cast<TiledLevel*>(FindObject("level"))->GetStartingTile()->GetDst();
	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &w, &h);

	m_objects.emplace_back("Player", new PlatformPlayer({ 0, 0, 77,h }, { s->x, s->y, static_cast<float>(77),static_cast<float>(h) }, TEMA::GetTexture("Knight")));

	//m_objects.emplace_back("Player", new PlatformPlayer({ 0, 0, 77,h }, { WIDTH / 2, HEIGHT - 64*3, static_cast<float>(77),static_cast<float>(h) }, TEMA::GetTexture("Knight")));

	//Slimes create
	SDL_QueryTexture(TEMA::GetTexture("Slime"), nullptr, nullptr, &w, &h);
	m_slimes.emplace_back(new Slime({ 0, 0, 35, 29 }, { WIDTH / 2, HEIGHT - 64 * 3, static_cast<float>(35), static_cast<float>(29) }, TEMA::GetTexture("Slime")));
	
	//m_objects.emplace_back("Player", new PlatformPlayer({ 0, 0, w / 14,h }, { r->x,r->y, static_cast<float>(w / 14),static_cast<float>(h) }, TEMA::GetTexture("Knight")));


	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/heart.png", "Spawn");
	SDL_QueryTexture(TEMA::GetTexture("Spawn"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("Spawn", new ItemObject({ 0,0,w,h }, { s->x,s->y, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("Spawn")));
	
	SDL_FRect* r = dynamic_cast<TiledLevel*>(FindObject("level"))->GetEndTile()->GetDst();
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Sign_End.png", "End");
	SDL_QueryTexture(TEMA::GetTexture("End"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("Trigger", new ItemObject({ 0,0,w,h }, { r->x,r->y, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("End")));
	
	SDL_QueryTexture(TEMA::GetTexture("HeartBar"), nullptr, nullptr, &w, &h);
	for(auto i = 0; i < dynamic_cast<PlatformPlayer*>(FindObject("Player"))->GetHeath(); i++)
	{
		auto* he = new Heart({ 0,0,w,h }, { static_cast<float>(10 + 30 * i), 50.0f, static_cast<float>(w),static_cast<float>(h) });
		Hearts.push_back(he);
		m_UIObject.emplace_back("HeartBar" + i, he);
	}
	m_objects.emplace_back("Label3", new Label("Minecraft", 28, 645, "Q", { 0,0,0,0 }));
	m_objects.emplace_back("Label4", new Label("Minecraft", 148, 645, "J", { 0,0,0,0 }));

	SDL_QueryTexture(TEMA::GetTexture("SwordSkill1"), nullptr, nullptr, &w, &h);
	m_pSwordSkill1 = new SwordSkill({ 0,0,w,h }, { 10,595, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("SwordSkill1"));
	m_UIObject.emplace_back("SwordSkill1", m_pSwordSkill1);

	std::cout << "Entering GameState..." << std::endl;


	//Load and play the game music
	SoundManager::Load("Aud/TownTheme.mp3", "gameLevel1", SOUND_MUSIC);
	SoundManager::PlayMusic("gameLevel1", -1);
	SoundManager::SetMusicVolume(30);

	


}

void GameState::CollisionCheck()
{
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	SDL_FRect* p = pp->GetBoundingBox();
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
			else if (p->x - pp->GetVelX() + 3 >= t->x + t->w)
			{ // Colliding with right side of tile.
				pp->StopX();
				pp->SetX(t->x + t->w);
			}
		}
	}

	//Player and slime collision
	for (int i = 0; i < m_slimes.size(); i++)
	{
		SDL_FRect* s = m_slimes[i]->GetDst();
		if (COMA::AABBCheck(*s, *p))
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
			if (pp->GetHeath() == 0)
			{
				STMA::ChangeState(new EndState());
			}
		}
	}

	// Use to test 
	if (COMA::AABBCheck(*p, *FindObject("Trigger")->GetDst()) && dynamic_cast<GameState*>(STMA::GetStates().back()))
	{
		if (EVMA::KeyPressed(SDL_SCANCODE_E))
		{
			STMA::ChangeState(new TitleState());
			//AnItem->Activate();
			//m_pWeapon->SetEnable(true);
		}
	}

	// This has to be at the end because of ChangeState
	if ((p->y >= HEIGHT + p->h && dynamic_cast<GameState*>(STMA::GetStates().back()) || EVMA::KeyPressed(SDL_SCANCODE_MINUS)))
	{
		//STMA::ChangeState(new EndState());
		pp->SetHeath(pp->GetHeath() -1);
		//auto ch = pp->GetMaxHealth() - pp->GetHeath();
		
		for(auto i = Hearts.size()-1; i > 0; --i )
		{
			if(!Hearts[i]->GetEmpty())
			{
				Hearts[i]->SetEmpty(true);
				
				break;
			}
		}
		
		//pp->SetY(0);
		auto s = FindObject("Spawn");
		MoveCamTo(s);
		pp->StopX();
		pp->StopY();

		pp->SetX(s->GetDst()->x);
		pp->SetY(s->GetDst()->y);
		//cout << s->x << endl;
		
		if(pp->GetHeath() == 0)
		{
			STMA::ChangeState(new EndState());
			SoundManager::StopMusic(); //The music will stop playing when the player dies (No more hearts)
		}
	}

	// Heal the player
	// Remove at beta
	if(EVMA::KeyPressed(SDL_SCANCODE_EQUALS) && pp->GetHeath() != pp->GetMaxHealth())
	{
		pp->SetHeath(pp->GetHeath() + 1);
		for (auto i = 0; i < Hearts.size() ; ++i)
		{
			if (Hearts[i]->GetEmpty())
			{
				Hearts[i]->SetEmpty(false);
				break;
			}
		}
	}

}

void GameState::MoveCamTo(GameObject* o)
{
	auto camOffset = (WIDTH / 2) - o->GetDst()->x;	
	for (int i = 0; i < dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles().size(); i++)
	{
		SDL_FRect* t = dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles()[i]->GetDst();
		t->x += camOffset;
	}
	FindObject("Spawn")->GetDst()->x += camOffset;
	FindObject("Player")->GetDst()->x += camOffset;
	FindObject("Trigger")->GetDst()->x += camOffset;
}

// This is kinda useless now
void GameState::UpdateCam(GameObject* o)
{
	//auto camOffset = (WIDTH / 2) - (o->GetDst()->x - (o->GetDst()->w / 2));
	float camspeed = 0.0;
	
	if (dynamic_cast<PlatformPlayer*>(o) != nullptr)
	{
		camspeed = dynamic_cast<PlatformPlayer*>(o)->GetVelX() * -1;
	}
	else if (o->GetDst()->x >= (WIDTH / 2) + 32)
	{
		//std::cout << "Right" << endl;
		camspeed = -32;
	}
	else if (o->GetDst()->x <= (WIDTH / 2) - 32)
	{
		//std::cout << "Left" << endl;
		camspeed = 32;
	}
	
	//cout << camOffset << endl;
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
	FindObject("Trigger")->GetDst()->x += camspeed;

	//dynamic_cast<Label*>(FindObject("Label6"))->SetText("Health: " + to_string(pp->GetHeath()) + "/" + to_string(pp->GetMaxHealth()));
}

void GameState::Update()
{
	MoveCamTo(FindObject("Player"));
	for (auto& m_object : m_objects)
		m_object.second->Update();
	CollisionCheck();
	if(EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState());
	}


	//if (EVMA::KeyHeld(SDL_SCANCODE_S))
	//{
	//	MoveCamTo(FindObject("Trigger"));
	//}
	//if (EVMA::KeyHeld(SDL_SCANCODE_G))
	//{
	//	MoveCamTo(FindObject("Player"));
	//}


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


	//SDL_Rect r { WIDTH / 2,HEIGHT/2,32,32 };
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &r);

	for (unsigned i = 0; i < m_slimes.size(); i++)
	{
		m_slimes[i]->Render();
	}

	
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

	for (auto& UI : m_UIObject)
	{
		delete UI.second;
		UI.second = nullptr;
	}
	m_UIObject.clear();
	Hearts.clear();

	for (unsigned i = 0; i < m_slimes.size(); i++)
	{
		delete m_slimes[i];
		m_slimes[i] = nullptr;
	}
	m_slimes.clear();
	m_slimes.shrink_to_fit();
	std::cout << "Exiting GameState..." << std::endl;
}

void GameState::Resume()
{
	cout << "Resuming GameState" << endl;
}
// End GameState