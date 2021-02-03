// Begin GameState
#include "GameState.h"

GameState::GameState() {}

void GameState::Enter()
{
	m_plabel = new Label("Minecraft", HEIGHT / 2, WIDTH / 2, "UWU What's this", { 0,0,0,0 });

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_RUNNING_AND_IDLE.png", "Knight");

	//SDL_Rect src{ 20,20,100,100 }, dir{0,0,100,100};
	int width, height;

	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &width, &height);
	m_player = new PlatformPlayer({ 0, 0, width / 14,height }, { WIDTH / 2,HEIGHT / 2, float(width / 14),float(height) }, Engine::Instance().GetRenderer(), TEMA::GetTexture("Knight"));
	m_player->Init();

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
			else if (m_player->GetDstP()->y - (float)m_player->GetVelY() >= (platform->y + platform->h))
			{//Collliding with the bottom side of the platform
				m_player->StopY();
				m_player->SetY(platform->y + platform->h);
			}

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

void GameState::UpdateCam()
{
	int camspeed = 0;
	if (m_player->GetDstP()->x > (WIDTH / 2) + 100)
	{
		//std::cout << "Right" << endl;
		m_camOffset = (WIDTH / 2) - (m_player->GetDstP()->x - (m_player->GetDstP()->w / 2));
		cout << m_camOffset << endl;
		camspeed = -5;
	}
	else if (m_player->GetDstP()->x < (WIDTH / 2) - 100)
	{
		//std::cout << "Left" << endl;
		m_camOffset = (WIDTH / 2) - (m_player->GetDstP()->x - ( m_player->GetDstP()->w / 2));
		cout << m_camOffset << endl;
		camspeed = 5;
	}

	for (auto &platform : m_pPlatforms)
	{
		platform->x += camspeed;
	}
	m_player->GetDstP()->x += camspeed;


}

void GameState::Update()
{
	//if (EVMA::KeyPressed(SDL_SCANCODE_N))
	//	STMA::ChangeState(new GameState());// Change to new GameState

	m_camOffset = 0;

	if (EVMA::KeyPressed(SDL_SCANCODE_H))
		m_player->ShowHitbox();

	if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_player->IsGrounded())
	{
		m_player->SetAccelY(-60.0); //<- JUMPFORCE
		m_player->SetGrounded(false);
	}

	if (EVMA::KeyDown(SDL_SCANCODE_A))
		m_player->SetAccelX(-1.0);
	if (EVMA::KeyDown(SDL_SCANCODE_D))
		m_player->SetAccelX(1.0);


	//Wrap the player
	if (m_player->GetDstP()->x < -51.0) m_player->SetX(1024.0);
	else if (m_player->GetDstP()->x > 1024.0) m_player->SetX(-50.0);

	m_player->Update();
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

	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), m_player->GetDstP());
	m_plabel->Render();
	m_player->Render();

	State::Render();
}

void GameState::Exit()
{

	for (auto& platform : m_pPlatforms)
	{
		delete platform;
		platform = nullptr;
	}
	
	std::cout << "Exiting TitleState..." << std::endl;
}

void GameState::Resume()
{
}
// End GameState