﻿#include "PauseState.h"


#include "SoundManager.h"
#include "StateManager.h"
#include "TextureManager.h"

PauseState::PauseState()
{
}

void PauseState::Enter()
{
	SOMA::Load("../GAME1017_Template_W01/Aud/mendelssohn_songs_without_words_opus_38_5.mp3", "Pause", SOUND_MUSIC);
	//Testing music remove later
	SOMA::SetMusicVolume(8);
	SOMA::PlayMusic("Pause");
	
	int w, h;
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/resume.png", "Back");
	SDL_QueryTexture(TEMA::GetTexture("Back"), nullptr, nullptr, &w, &h);
	m_pbutton = new BoolButton({ 0,0,w/3,h }, { WIDTH / 2 - (float)w / 6,HEIGHT / 2,(float)w/3, (float)h }, TEMA::GetTexture("Back"));
	m_objects.emplace_back("button", m_pbutton);

	SDL_QueryTexture(TEMA::GetTexture("Exit"), nullptr, nullptr, &w, &h);
	m_pbutton2 = new BoolButton({ 0,0,w / 2,h }, { WIDTH / 2 - (float)w / 6, HEIGHT / 1.65,(float)w / 2, (float)h }, TEMA::GetTexture("Exit"));
	m_objects.emplace_back("button2", m_pbutton2);

	m_pBackground = new SDL_FRect({ 0, 0, (float)WIDTH, (float)HEIGHT });
	std::cout << "Entering PauseState" << endl;
	
	cout << "Entering PauseState" << endl;
}

void PauseState::Update()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Update();
	
	if(m_pbutton->GetChangeState() || EVMA::KeyPressed(SDL_SCANCODE_R))
	{
		STMA::PopState();
	}
	else if (m_pbutton2->GetChangeState() || EVMA::KeyPressed(SDL_SCANCODE_E))
	{
		STMA::PopState();
		STMA::ChangeState(new TitleState());
	}
}

void PauseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 128);
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &SDL_FRect({ 0, 0, (float)WIDTH, (float)HEIGHT }));
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), m_pBackground);
	
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();

	State::Render();
}

void PauseState::Exit()
{
	SOMA::StopMusic();
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
	cout << "Exiting PauseState" << endl;
}
