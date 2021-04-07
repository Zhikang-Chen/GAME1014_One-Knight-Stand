#include "PauseState.h"
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
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/save button.png", "Save");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/load button.png", "Load");
	SDL_QueryTexture(TEMA::GetTexture("Back"), nullptr, nullptr, &w, &h);
	m_pbutton = new ReturnButton({ 0,0,w/2,h }, { WIDTH / 2 - (float)w / 6,HEIGHT - 480,(float)w/2, (float)h }, TEMA::GetTexture("Back"));
	m_objects.emplace_back("button", m_pbutton);

	SDL_QueryTexture(TEMA::GetTexture("Exit"), nullptr, nullptr, &w, &h);
	m_pbutton2 = new TitleButton({ 0,0,w / 2,h }, { WIDTH / 2 - (float)w / 6, HEIGHT - 270,(float)w / 2, (float)h }, TEMA::GetTexture("Exit"));
	m_objects.emplace_back("button2", m_pbutton2);

	SDL_QueryTexture(TEMA::GetTexture("Save"), nullptr, nullptr, &w, &h);
	m_pbutton3 = new SaveButton({ 0,0,w / 2,h }, { WIDTH / 2 - (float)w / 6,HEIGHT-410,(float)w / 2, (float)h }, TEMA::GetTexture("Save"));
	m_objects.emplace_back("button3", m_pbutton3);

	SDL_QueryTexture(TEMA::GetTexture("Load"), nullptr, nullptr, &w, &h);
	m_pbutton4 = new LoadButton({ 0,0,w / 2,h }, { WIDTH / 2 - (float)w / 6, HEIGHT- 340,(float)w / 2, (float)h }, TEMA::GetTexture("Load"));
	m_objects.emplace_back("button4", m_pbutton4);

	m_pBackground = new SDL_FRect({ 0, 0, (float)WIDTH, (float)HEIGHT });
	std::cout << "Entering PauseState" << endl;
	
	cout << "Entering PauseState" << endl;
}

void PauseState::Update()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Update();
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
