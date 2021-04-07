#include "Engine.h"
#include "EndState.h"
#include "GameClearState.h"
#include "EventManager.h"
#include "StateManager.h"
#include "SoundManager.h"

GameClearState::GameClearState() {}

void GameClearState::Enter()
{
	//Width and height variables
	int w, h;

	//Print message to console
	std::cout << "Game Clear State" << std::endl;
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Winner.png", "GameClear");


	SDL_QueryTexture(TEMA::GetTexture("GameClear"), nullptr, nullptr, &w, &h);
	m_gClearBackground = new Background({ 0,0,(int)w,(int)h }, { 0,0, (float)w - 0, (float)h + 0 }, TEMA::GetTexture("GameClear"));
	m_objects.emplace_back("GameClear", m_gClearBackground);


	auto* instructionText = new Label("Minecraft", WIDTH / 2, HEIGHT / 2, "Click to return to the Title Screen", SDL_Color{ 0,0,0,0 });
	m_objects.emplace_back("SubText", instructionText);
	instructionText->SetPos((WIDTH - instructionText->GetDst()->w) / 2, HEIGHT / 3);

}

void GameClearState::Update()
{

	//Mouse is clicked, return to title screen
	if (EVMA::MousePressed(1))
	{
		STMA::ChangeState(new TitleState());
	}
}

void GameClearState::Render()
{

	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();

	
	State::Render();
}

void GameClearState::Exit()
{

	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
	std::cout << "Exiting Game Clear State" << std::endl;
}


