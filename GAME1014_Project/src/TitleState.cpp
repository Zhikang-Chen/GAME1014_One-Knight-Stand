// Begin TitleState
#include "TitleState.h"

#include "CollisionManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "GameState.h"
#include "StateManager.h"
#include "TextureManager.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	m_plabel = new Label("Minecraft", HEIGHT/2, WIDTH/2, "UWU What's this", {0,0,0,0});

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_RUNNING_AND_IDLE.png", "Knight");
	
	//SDL_Rect src{ 20,20,100,100 }, dir{0,0,100,100};
	int width, height;
	
	SDL_QueryTexture(TEMA::GetTexture("Knight"), nullptr, nullptr, &width, &height);	
	m_player = new PlatformPlayer({ 0, 0, width/14,height }, { WIDTH / 2,HEIGHT / 2, float(width / 14),float(height) }, Engine::Instance().GetRenderer(), TEMA::GetTexture("Knight"));
	m_player->Init();
	m_platforms = new SDL_FRect[5];
	m_platforms[0] = { 462, 648, 100, 20 }; //0
	m_platforms[1] = {200, 468, 100, 20};  //1
	m_platforms[2] = {724, 468, 100, 20};  //2
	m_platforms[3] = {462, 368, 100, 40};  //3
	m_platforms[4] = {-100, 668, 1000, 100};
	
	//std::cout << "Entering TitleState..." << std::endl;
}


/*
I SPENT 5 HOURS TRYING TO FIGURE OUT WHY DOESN'T THE COLLISION CHECK WORK....
IT WAS A SEMICOLON AT THE END OF THE IF STATEMENT. A FUCKING SEMICOLON!
I HAVEN'T BEEN THIS CLOSE TO KILLING MYSELF SINCE LAST SUMMER.
I am not only an idiot I am also blind.
*/

//Check collision between platforms and the player
void TitleState::CollisionCheck()
{
	for (int i = 0; i < 5; i++)
	{
		if (COMA::AABBCheck(m_platforms[i], m_player->GetDst()))
		{
			//cout << m_player->GetDstP()->h << endl;
			if ((m_player->GetDstP()->y + m_player->GetDstP()->h) - (float)m_player->GetVelY() <= m_platforms[i].y)
			{//Collliding with the top side of the platform
				m_player->SetGrounded(true);
				m_player->StopY();
				m_player->SetY(m_platforms[i].y - m_player->GetDstP()->h);
				//cout << "insanity" << endl;
			}
			else if (m_player->GetDstP()->y - (float)m_player->GetVelY() >= (m_platforms[i].y + m_platforms[i].h))
			{//Collliding with the bottom side of the platform
				m_player->StopY();
				m_player->SetY(m_platforms[i].y + m_platforms[i].h);
			}

			else if ((m_player->GetDstP()->x + m_player->GetDstP()->w) - (float)m_player->GetVelX() <= m_platforms[i].x)
			{//Collliding with the left side of the platform
				m_player->StopX();
				m_player->SetX(m_platforms[i].x - m_player->GetDstP()->w);
			}

			else if (m_player->GetDstP()->x - (float)m_player->GetVelX() >= (m_platforms[i].x + m_platforms[i].w))
			{//Collliding with the right side of the platform
				m_player->StopX();
				m_player->SetX(m_platforms[i].x + m_platforms[i].w);
			}
		}
	}
}

void TitleState::Update()
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

	if (m_player->GetDstP()->x > (WIDTH / 2) + 100 )
	{
		std::cout << "Right" << endl;
		m_camOffset = (WIDTH / 2) - (m_player->GetDstP()->x - (m_player->GetDstP()->w / 2));
		cout << m_camOffset;
	}

	else if (m_player->GetDstP()->x < (WIDTH / 2) - 100)
	{
		std::cout << "Left" << endl;
		m_camOffset = (WIDTH / 2) - (m_player->GetDstP()->x - ( m_player->GetDstP()->w / 2));
		cout << m_camOffset;
	}
	
	int camspeed = 0;
	if (m_camOffset > 0)
	{
		camspeed = 5;
		//if (m_camOffset > 100)
		//{
		//	camspeed = 10;
		//}
	}
	else if(m_camOffset < 0)
	{
		camspeed = -5;
		//if (m_camOffset > -100)
		//{
		//	camspeed = -10;
		//}
	}

	for (int i = 0; i < 5; i++)
	{
		m_platforms[i].x += camspeed;
	}
	m_player->GetDstP()->x += camspeed;
	
	
	//m_camOffset = (WIDTH / 2) - m_player->GetDstP()->y;
}

void TitleState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRectsF(Engine::Instance().GetRenderer(), m_platforms,5);

	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), m_player->GetDstP());
	m_plabel->Render();
	m_player->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
