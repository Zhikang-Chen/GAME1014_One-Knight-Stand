// Begin GameState
#include "GameState.h"
#include "Engine.h"
#include "StateManager.h"
#include "EventManager.h"
#include "TitleState.h"

GameState::GameState() {}

void GameState::Enter() // Used for initialization.
{
	std::cout << "Entering GameState..." << std::endl;
}

void GameState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_X))
		STMA::ChangeState(new TitleState());// Change to new TitleState
}

void GameState::Render()
{
	std::cout << "Rendering GameState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;
}

void GameState::Resume()
{
	std::cout << "Resuming GameState..." << std::endl;
}
// End GameState