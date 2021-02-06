// Begin TitleState
#include "TitleState.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/DotC-LgXoAMrpqi.png", "Background_1");
	int width, height;
	SDL_QueryTexture(TEMA::GetTexture("Background_1"), nullptr, nullptr, &width, &height);
	m_pBackground = new Background({ 0,0,(int)width,(int)height }, {0,0, (float)width*5, (float)height*5 }, TEMA::GetTexture("Background_1"));
	m_objects.emplace("Background", m_pBackground);
	
	m_pSubTitle = new Label("Minecraft",WIDTH / 20, HEIGHT / 7, "Insert sub title here", { 0,0,0,0 });
	m_objects.emplace("Subtitle", m_pSubTitle);
	
	m_pTitle = new Label("Genshi_font", WIDTH / 25, HEIGHT / 27, "One Knight Stand", { 0,0,0,0 });
	m_objects.emplace("Title", m_pTitle);

	something = new Label("Minecraft", WIDTH /25, HEIGHT - 50, "Press 'n' to get to game state. I am too lazy to code the button ", { 0,0,0,0 });
	m_objects.emplace("idk", something);
	//std::cout << "Entering TitleState..." << std::endl;
}


void TitleState::Update()
{
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Update();
	
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
		STMA::ChangeState(new GameState());// Change to new GameState
}

void TitleState::Render()
{
	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	
	//m_pBackground->Render();
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
