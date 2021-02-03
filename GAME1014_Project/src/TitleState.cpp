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

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/aPlayer.png", "life");
	
	//SDL_Rect src{ 20,20,100,100 }, dir{0,0,100,100};
	int width, height;
	
	SDL_QueryTexture(TEMA::GetTexture("life"), nullptr, nullptr, &width, &height);	
	fml = new PlatformPlayer({ 0,0, width,height }, { 0,0, float(width),float(height) }, Engine::Instance().GetRenderer(), TEMA::GetTexture("life"));
	fml->Init();
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
		if (COMA::AABBCheck(m_platforms[i], fml->GetDst()))
		{
			//cout << fml->GetDstP()->h << endl;
			if ((fml->GetDstP()->y + fml->GetDstP()->h) - (float)fml->GetVelY() <= m_platforms[i].y)
			{//Collliding with the top side of the platform
				fml->SetGrounded(true);
				fml->StopY();
				fml->SetY(m_platforms[i].y - fml->GetDstP()->h);
				//cout << "insanity" << endl;
			}
			else if (fml->GetDstP()->y - (float)fml->GetVelY() >= (m_platforms[i].y + m_platforms[i].h))
			{//Collliding with the bottom side of the platform
				fml->StopY();
				fml->SetY(m_platforms[i].y + m_platforms[i].h);
			}

			else if ((fml->GetDstP()->x + fml->GetDstP()->w) - (float)fml->GetVelX() <= m_platforms[i].x)
			{//Collliding with the left side of the platform
				fml->StopX();
				fml->SetX(m_platforms[i].x - fml->GetDstP()->w);
			}

			else if (fml->GetDstP()->x - (float)fml->GetVelX() >= (m_platforms[i].x + m_platforms[i].w))
			{//Collliding with the right side of the platform
				fml->StopX();
				fml->SetX(m_platforms[i].x + m_platforms[i].w);
			}
		}
	}
}

void TitleState::Update()
{
	//if (EVMA::KeyPressed(SDL_SCANCODE_N))
	//	STMA::ChangeState(new GameState());// Change to new GameState

	if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && fml->IsGrounded())
	{
		fml->SetAccelY(-60.0); //<- JUMPFORCE
		fml->SetGrounded(false);
	}

	if (EVMA::KeyDown(SDL_SCANCODE_A))
		fml->SetAccelX(-1.0);
	if (EVMA::KeyDown(SDL_SCANCODE_D))
		fml->SetAccelX(1.0);

	//Wrap the player
	if (fml->GetDstP()->x < -51.0) fml->SetX(1024.0);
	else if (fml->GetDstP()->x > 1024.0) fml->SetX(-50.0);
	
	fml->Update();
	CollisionCheck();
}

void TitleState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRectsF(Engine::Instance().GetRenderer(), m_platforms,5);

	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), fml->GetDstP());
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &MAMA::ConvertFRect2Rect(fml->GetDst()));
	m_plabel->Render();
	fml->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
