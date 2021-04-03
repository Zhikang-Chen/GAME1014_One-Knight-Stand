#include "LoadState.h"
//#include <iostream>
#include "Engine.h"
#include "StateManager.h"
#include "SoundManager.h"

void LoadState::Enter()
{
	std::cout << "Entering Load State" << std::endl;
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/aPlayer.png", "LoadKnight");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/sword.png", "LoadSword");

	auto LP = new Label("Genshi_font", WIDTH / 2, HEIGHT / 2, "Loading", SDL_Color{ 255,255,255,255 });
	m_objects.emplace_back("Loading Text", LP);
	LP->SetPos((WIDTH - LP->GetDst()->w) / 2, HEIGHT / 4);


	auto L = new Label("Minecraft", WIDTH / 2, HEIGHT / 2, "0%", SDL_Color{ 255,255,255,255 });
	m_objects.emplace_back("Load", L);
	L->SetPos((WIDTH - L->GetDst()->w) / 2, LP->GetDst()->y + LP->GetDst()->h);
	
	// Adds an Image
	int width, height;
	SDL_QueryTexture(TEMA::GetTexture("LoadKnight"), nullptr, nullptr, &width, &height);
	m_objects.emplace_back("Knight", new SpriteObject({ 0,0,width, height }, { (WIDTH / 2) - (float)width / 4 ,HEIGHT / 2, (float)width,(float)height }, TEMA::GetTexture("LoadKnight")));

	SDL_QueryTexture(TEMA::GetTexture("LoadSword"), nullptr, nullptr, &width, &height);
	LoadSword = new SpriteObject({ 0,0,width, height }, { (WIDTH / 2) + (float)(width/1.5) ,HEIGHT / 2, (float)width,(float)height }, TEMA::GetTexture("LoadSword"));
	m_objects.emplace_back("sword", LoadSword);
	m_frame = 0;
	m_endFrame = 600 + rand()%6000;

	//cout << m_endFrame << endl;
	
}

void LoadState::Update()
{
	m_frame++;
	if(m_frame > m_endFrame)
	{
		STMA::PopState();
		return;
	}
	
	// Spin the image
	LoadSword->SetAngle(LoadSword->GetAngle() + 10);
	int number = (float)m_frame / m_endFrame * 100;
	dynamic_cast<Label*>(FindObject("Load"))->SetText(to_string(number)+'%');
	
}

void LoadState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();

	if (dynamic_cast<LoadState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
		State::Render();
}

void LoadState::Exit()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
	std::cout << "Exiting Load State" << std::endl;
}

void LoadState::Resume()
{

}

