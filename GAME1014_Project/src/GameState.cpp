// Begin GameState
#include "GameState.h"

GameState::GameState() {}

void GameState::Enter()
{
	//m_plabel = new Label("Minecraft", HEIGHT / 2, WIDTH / 2, "UWU? What's dis", { 0,0,0,0 });

	//Ui test and i am not sorry for typing those
	//Remove when use
	m_objects.emplace("Label", new Label("Minecraft", WIDTH / 2, HEIGHT / 2 + 20, "UWU? What's dis", { 0,0,0,0 }));
	m_objects.emplace("Label2", new Label("Minecraft", WIDTH / 2, HEIGHT / 2 + 40, "I am your cute UI GF", { 0,0,0,0 }));
	m_objects.emplace("Label3", new Label("Minecraft", 10, 40, "I luv u OWO", { 0,0,0,0 }));

	m_objects.emplace("Label4", new Label("Minecraft", WIDTH / 2 - 20, 10, "I am not responsible for the lost of your sanity -Ken", { 0,0,0,0 }));

	
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_RUNNING_AND_IDLE.png", "Knight");

	//SDL_Rect src{ 20,20,100,100 }, dir{0,0,100,100};
	int width, height;

	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &width, &height);
	m_player = new PlatformPlayer({ 0, 0, width / 14,height }, { WIDTH / 2,HEIGHT / 2, float(width / 14),float(height) }, TEMA::GetTexture("Knight"));
	m_objects.emplace("Player", m_player);

	m_pPlatforms.push_back(new SDL_FRect { 462, 648, 100, 20 }); //0
	m_pPlatforms.push_back(new SDL_FRect{ 200, 468, 100, 20 });  //1
	m_pPlatforms.push_back(new SDL_FRect{ 724, 468, 100, 20 });  //2
	m_pPlatforms.push_back(new SDL_FRect{ 462, 368, 100, 40 });  //3
	m_pPlatforms.push_back(new SDL_FRect{ -100, 668, 10000, 100 });

	//std::cout << "Entering TitleState..." << std::endl;
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
	for(auto &platform : m_pPlatforms)
	{
		if (COMA::AABBCheck(platform, m_player->GetDstP()))
		{
			//cout << m_player->GetDstP()->h << endl;
			if ((m_player->GetDstP()->y + m_player->GetDstP()->h) - (float)m_player->GetVelY() <= platform->y)
			{//Collliding with the top side of the platform
				m_player->SetGrounded(true);
				m_player->StopY();
				m_player->SetY(platform->y - m_player->GetDstP()->h);
				//cout << "insanity" << endl;
			}
			//else if (m_player->GetDstP()->y - (float)m_player->GetVelY() >= (platform->y + platform->h))
			//{//Collliding with the bottom side of the platform
			//	m_player->StopY();
			//	m_player->SetY(platform->y + platform->h);
			//}

			else if ((m_player->GetDstP()->x + m_player->GetDstP()->w) - (float)m_player->GetVelX() <= platform->x)
			{//Collliding with the left side of the platform
				m_player->StopX();
				m_player->SetX(platform->x - m_player->GetDstP()->w);
			}

			else if (m_player->GetDstP()->x - (float)m_player->GetVelX() >= (platform->x + platform->w))
			{//Collliding with the right side of the platform
				m_player->StopX();
				m_player->SetX(platform->x + platform->w);
			}
		}
	}
}

/*To do
 *Fix a bug where the player can get out of bound vai jumping
 */

void GameState::UpdateCam()
{
	int camspeed = 0;
	if (m_player->GetDstP()->x >= (WIDTH / 2) + 100)
	{
		//std::cout << "Right" << endl;
		//m_camOffset = (WIDTH / 2) - (m_player->GetDstP()->x - (m_player->GetDstP()->w / 2));
		//cout << m_camOffset << endl;
		camspeed = -7;
	}
	else if (m_player->GetDstP()->x <= (WIDTH / 2) - 100)
	{
		//std::cout << "Left" << endl;
		//m_camOffset = (WIDTH / 2) - (m_player->GetDstP()->x + ( m_player->GetDstP()->w / 2));
		//cout << m_camOffset << endl;
		camspeed = 7;
	}

	for (auto& platform : m_pPlatforms)
	{
		platform->x += camspeed;
	}
	m_objects["Label4"]->GetDst()->x += camspeed;
	m_player->SetX(m_player->GetDstP()->x + camspeed);


}

void GameState::Update()
{
	
	//m_plabel->SetText());
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Update();
	
	CollisionCheck();
	UpdateCam();

}

void GameState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);

	for(auto &platform : m_pPlatforms)
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), platform);
	
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();
	if (dynamic_cast<GameState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
		State::Render();
	
	State::Render();
}

void GameState::Exit()
{

	for (auto& platform : m_pPlatforms)
	{
		delete platform;
		platform = nullptr;
	}

	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
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