// Begin TitleState
#include "TitleState.h"
#include "Engine.h"
#include "EventManager.h"
#include "GameState.h"
#include "StateManager.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	m_plabel = new Label("Minecraft", HEIGHT/2, WIDTH/2, "Fuck my life", {0,0,0,0});
	//std::cout << "Entering TitleState..." << std::endl;
}

void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
		STMA::ChangeState(new GameState());// Change to new GameState
}

void TitleState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);

	m_plabel->Render();
	
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
