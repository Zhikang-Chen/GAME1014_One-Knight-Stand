#include "PauseState.h"


#include "SoundManager.h"
#include "StateManager.h"
#include "TextureManager.h"

PauseState::PauseState()
{
}

void PauseState::Enter()
{
	SOMA::PlayMusic("Pause");
	int w, h;	
	SDL_QueryTexture(TEMA::GetTexture("Back"), nullptr, nullptr, &w, &h);
	//m_pbutton = new BoolButton({ 0,0,w,h }, { WIDTH / 2 - (float)w / 2,HEIGHT / 2,(float)w, (float)h }, TEMA::GetTexture("Back"));
	//m_objects.push_back(pair<string, GameObject*>("button", m_pbutton));
	cout << "Entering PauseState" << endl;
}

void PauseState::Update()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Update();

	if(EVMA::KeyPressed(SDL_SCANCODE_R))
	{
		STMA::PopState();
	}
	
	//if(m_pbutton->GetChangeState())
	//{
	//	STMA::PopState();
	//}
}

void PauseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 128);
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &SDL_FRect({ 0, 0, (float)WIDTH, (float)HEIGHT }));
	
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();

	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting PauseState" << endl;
}
