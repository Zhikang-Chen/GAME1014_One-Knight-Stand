// Begin GameState
#include "GameState.h"
#include "Engine.h"
#include "StateManager.h"

GameState::GameState() {}

void GameState::Enter() // Used for initialization.
{
	cout << "Entering GameState..." << endl;
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
		STMA::ChangeState(new TitleState());// Change to new TitleState
}

void GameState::Render()
{
	cout << "Rendering GameState..." << endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void GameState::Exit()
{
	cout << "Exiting GameState..." << endl;
}

void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
}
// End GameState