// Begin TitleState
#include "TitleState.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	m_plabel = new Label("Minecraft", HEIGHT / 2, WIDTH / 2, "Press n to gamestate", { 0,0,0,0 });
	
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
	SDL_RenderClear(Engine::Instance().GetRenderer());

	m_plabel->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
