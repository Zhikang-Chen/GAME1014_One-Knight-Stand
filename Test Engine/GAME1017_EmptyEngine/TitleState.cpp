// Begin TitleState
#include "TitleState.h"
#include "Engine.h"
#include "StateManager.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	cout << "Entering TitleState..." << std::endl;
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
		STMA::ChangeState(new GameState());// Change to new GameState
}

void TitleState::Render()
{
	cout << "Rendering TitleState..." << endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting TitleState..." << endl;
}
// End TitleState