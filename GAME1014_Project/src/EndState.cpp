#include "EndState.h"

#include <iostream>
#include "Engine.h"
#include "StateManager.h"

void EndState::Enter()
{
	std::cout << "Entering End State" << std::endl;
	m_objects.emplace("GameoverText", new Label("Genshi_font", WIDTH/2, HEIGHT/2, "Game Over", SDL_Color{ 255,255,255,255 }));
	Label* LP = dynamic_cast<Label*>(m_objects["GameoverText"]);
	LP->SetPos((WIDTH - LP->GetDst()->w)/2, HEIGHT / 4);

	m_objects.emplace("SubText", new Label("Minecraft", WIDTH / 2, HEIGHT / 2, "Press anywhere to get back to title", SDL_Color{ 255,255,255,255 }));
	Label* ST = dynamic_cast<Label*>(m_objects["SubText"]);
	ST->SetPos((WIDTH - ST->GetDst()->w) / 2, HEIGHT / 3);

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/20191103_131848.png", "NoIdea");
	int width, height;
	SDL_QueryTexture(TEMA::GetTexture("NoIdea"), nullptr, nullptr, &width, &height);
	m_objects.emplace("image", new SpriteObject({0,0,width, height }, {( WIDTH/2 ) - (float)width/4 ,HEIGHT / 2, (float)width/2,(float)height/2 }, TEMA::GetTexture("NoIdea")));
	
 }

void EndState::Update()
{
	if(EVMA::MousePressed(1))
	{
		STMA::ChangeState(new TitleState());
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0,0,0,255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();
	
	if (dynamic_cast<EndState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
		State::Render();
}

void EndState::Exit()
{
	std::cout << "Exiting End State" << std::endl;
}

void EndState::Resume()
{
	
}
