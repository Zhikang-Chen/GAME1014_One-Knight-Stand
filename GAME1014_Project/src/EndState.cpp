#include "EndState.h"

#include <iostream>
#include "Engine.h"
#include "StateManager.h"
#include "SoundManager.h"

void EndState::Enter()
{
	std::cout << "Entering End State" << std::endl;
	
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/GAME_OVER.png", "NoIdea");
	auto* LP = new Label("Genshi_font", WIDTH / 2, HEIGHT / 2, "Game Over", SDL_Color{ 255,255,255,255 });
	m_objects.emplace_back("GameoverText", LP);	
	//Label* LP = dynamic_cast<Label*>(m_objects.get);
	LP->SetPos((WIDTH - LP->GetDst()->w)/2, HEIGHT / 4);

	// Add text
	auto* ST = new Label("Minecraft", WIDTH / 2, HEIGHT / 2, "Press anywhere to get back to title", SDL_Color{ 255,255,255,255 });
	m_objects.emplace_back("SubText", ST);
	ST->SetPos((WIDTH - ST->GetDst()->w) / 2, HEIGHT / 3);

	// Adds an Image
	int width, height;
	SDL_QueryTexture(TEMA::GetTexture("NoIdea"), nullptr, nullptr, &width, &height);
	m_objects.emplace_back("image", new SpriteObject({0,0,width, height }, {( WIDTH/2 ) - (float)width/4 ,HEIGHT / 2, (float)width/2,(float)height/2 }, TEMA::GetTexture("NoIdea")));

	SOMA::Load("../GAME1017_Template_W01/Aud/game_over.mp3", "gameOver", SOUND_MUSIC);
	SOMA::SetMusicVolume(15);
	SOMA::PlayMusic("gameOver");

 }

void EndState::Update()
{
	// Spin the image
	//SpriteObject* I = dynamic_cast<SpriteObject*>(FindObject("image"));
	//I->SetAngle(++I->GetAngle());
	
	if(EVMA::MousePressed(1))
	{
		STMA::ChangeState(new TitleState());
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0,0,0,255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();
	
	if (dynamic_cast<EndState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
		State::Render();
}

void EndState::Exit()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
	std::cout << "Exiting End State" << std::endl;
}

void EndState::Resume()
{
	
}
