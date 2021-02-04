// Begin TitleState
#include "TitleState.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/DotC-LgXoAMrpqi.png", "Background_1");
	int width, height;
	SDL_QueryTexture(TEMA::GetTexture("Background_1"), nullptr, nullptr, &width, &height);
	m_pBackground = new Sprite({ 0,0,(int)width,(int)height }, {0,0, (float)width*5, (float)height*5 }, Engine::Instance().GetRenderer(), TEMA::GetTexture("Background_1"));
	
	m_pSubTitle = new Label("Minecraft",WIDTH / 20, HEIGHT / 7, "Insert sub title here", { 0,0,0,0 });

	m_pTitle = new Label("Genshi_font", WIDTH / 25, HEIGHT / 27, "One Knight Stand", { 0,0,0,0 });

	something = new Label("Minecraft", WIDTH /25, HEIGHT - 50, "Press 'n' to get to game state. I am too lazy to put the button ", { 0,0,0,0 });
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
	
	m_pBackground->Render();
	m_pTitle->Render();
	m_pSubTitle->Render();
	something->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
