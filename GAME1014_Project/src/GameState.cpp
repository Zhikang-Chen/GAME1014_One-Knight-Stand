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
	m_objects.emplace_back("Label3", new Label("Minecraft", 10, 40, "I luv u OWO", { 0,0,0,0 }));
	m_objects.emplace_back("Label4", new Label("Minecraft", WIDTH / 2 - 20, 10, "I am not responsible for the lost of your sanity -Ken", { 0,0,0,0 }));
	m_objects.emplace_back("Label5", new Label("Minecraft", WIDTH + 200, 10, "You can't run human kun", { 0,0,0,0 }));
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_RUNNING_AND_IDLE.png", "Knight");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/sword.png", "IDK");
	
	//SDL_Rect src{ 20,20,100,100 }, dir{0,0,100,100};

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Tileset.png", "tiles");
	m_objects.emplace_back("level", new TiledLevel(24, 249, 32, 32, "../GAME1017_Template_W01/Dat/Tiledata.txt", "../GAME1017_Template_W01/Dat/Mario_test.txt", "tiles"));
	
	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &w, &h);
	//m_player = new PlatformPlayer({ 0, 0, width / 14,height }, { 0,0, float(width / 14),float(height) }, TEMA::GetTexture("Knight"));
	m_objects.emplace_back("Player", new PlatformPlayer({ 0, 0, w / 14,h }, { WIDTH/2,0, static_cast<float>(w / 14),static_cast<float>(h) }, TEMA::GetTexture("Knight")));

	SDL_QueryTexture(TEMA::GetTexture("IDK"), nullptr, nullptr, &w, &h);
	m_pWeapon = new Sword({ 0,0,w,h }, { 0,0, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("IDK"));

	//Use to test item class remove when done
	m_pWeapon->SetTarget(FindObject("Player")->GetDst());
	m_pWeapon->SetEnable(false);
	m_objects.emplace_back("sword", m_pWeapon);
	

	SDL_QueryTexture(TEMA::GetTexture("IDK"), nullptr, nullptr, &w, &h);
	AnItem = new ItemObject({ 0,0,w,h }, { 0,650, static_cast<float>(w),static_cast<float>(h) }, TEMA::GetTexture("IDK"));
	m_objects.emplace_back("Weapon", AnItem);
	
	std::cout << "Entering TitleState..." << std::endl;
}



/*
I SPENT 5 HOURS TRYING TO FIGURE OUT WHY DOESN'T THE COLLISION CHECK WORK....
IT WAS A SEMICOLON AT THE END OF THE IF STATEMENT. A FUCKING SEMICOLON!
I HAVEN'T BEEN THIS CLOSE TO KILLING MYSELF SINCE LAST SUMMER.
I am not only an idiot I am also blind.
*/

//Check collision between platforms and the player
void GameState::CollisionCheck()
{
	SDL_FRect* p = FindObject("Player")->GetDst(); // Copies address of player m_dst.
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	for (int i = 0; i < dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles().size(); i++)
	{
		SDL_FRect* t = dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles()[i]->GetDst();
		if (COMA::AABBCheck(*p, *t)) // Collision check between player rect and tile rect.
		{
			if ((p->y + p->h) - static_cast<float>(pp->GetVelY()) <= t->y)
			{ // Colliding with top side of tile.
				pp->StopY();
				pp->SetY(t->y - p->h);
				pp->SetGrounded(true);
			}
			//else if (p->y - static_cast<float>(pp->GetVelY()) >= (t->y + t->h))
			//{ // Colliding with bottom side of tile.
			//	pp->StopY();
			//	pp->SetY(t->y + t->h);
			//}
			else if ((p->x + p->w) - static_cast<float>(pp->GetVelX()) <= t->x)
			{ // Colliding with left side of tile.
				pp->StopX();
				cout << "Heading Right: " << pp->GetVelX() << endl;
				pp->SetX(t->x - p->w);
			}
			else if (p->x  - static_cast<float>(pp->GetVelX()) >= (t->x + t->w))
			{ // Colliding with right side of tile.
				pp->StopX();
				cout << "Heading Left: " << pp->GetVelX() << endl;
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
	if (p->y >= HEIGHT)
	{
		STMA::ChangeState(new EndState());
	}
	
	//cout << pp->GetVelX() << endl;
}

/*To do
 *Fix a bug where the player can get out of bound vai jumping
 */

void GameState::UpdateCam()
{
	float camspeed = 0.0;
	PlatformPlayer* pp = dynamic_cast<PlatformPlayer*>(FindObject("Player"));
	if (pp->GetDst()->x >= (WIDTH / 2) + 64)
	{
		//std::cout << "Right" << endl;
		//m_camOffset = (WIDTH / 2) - (m_player->GetDst()->x - (m_player->GetDst()->w / 2));
		//cout << m_camOffset << endl;
		camspeed = -8.0f;
	}
	else if (pp->GetDst()->x <= (WIDTH / 2) - 64)
	{
		//std::cout << "Left" << endl;
		//m_camOffset = (WIDTH / 2) - (m_player->GetDst()->x + ( m_player->GetDst()->w / 2));
		//cout << m_camOffset << endl;
		camspeed = 8.0f;
	}

	for (int i = 0; i < dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles().size(); i++)
	{
		SDL_FRect* t = dynamic_cast<TiledLevel*>(FindObject("level"))->GetObstacles()[i]->GetDst();
		t->x += camspeed;
	}
	
	FindObject("Label4")->GetDst()->x += camspeed;
	FindObject("Label5")->GetDst()->x += camspeed;
	FindObject("Player")->GetDst()->x += camspeed;
	
	FindObject("Weapon")->GetDst()->x += camspeed;

}

void GameState::Update()
{
	UpdateCam();
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Update();
	CollisionCheck();

	if(EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState);
	}

	
}

void GameState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();
	
	if (dynamic_cast<GameState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
		State::Render();
	
}

void GameState::Exit()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
	
	std::cout << "Exiting TitleState..." << std::endl;
}

void GameState::Resume()
{
}
// End GameState