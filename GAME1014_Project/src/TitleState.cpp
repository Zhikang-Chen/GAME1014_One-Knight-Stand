// Begin TitleState
#include "TitleState.h"
#include "EndState.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "StateManager.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/DotC-LgXoAMrpqi.png", "Background_1");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/titlescreen.jpg", "Background_2");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/Knight_Concept_ALL_ANIMATION-Sheet.png", "bleh");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/p.png", "Play");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/e.png", "Exit");
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/new_game.png", "NG");

	
	int w, h;
	SDL_QueryTexture(TEMA::GetTexture("Background_2"), nullptr, nullptr, &w, &h);

	m_objects.emplace_back("Background", new Background({ 0,0,(int)w,(int)h }, { -380,0, (float)w - 400, (float)h - 280 }, TEMA::GetTexture("Background_2")));
	m_objects.emplace_back("Subtitle", new Label("Pixel", 0,0, "Devs: OPRON", { 0,0,0,0 }));
	auto l = dynamic_cast<Label*>(FindObject("Subtitle"));
	l->SetPos(WIDTH / 2 - l->GetDst()->w/2, HEIGHT - l->GetDst()->h);
	m_objects.emplace_back("Title", new Label("Bbold", 50 + WIDTH / 25, 160 + HEIGHT / 27, "One Knight Stand", { 0,0,0,0 }));

	SDL_QueryTexture(TEMA::GetTexture("bleh"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("bleh", new Background({ 0, 0, 77,h }, { 486, 295, static_cast<float>(77),static_cast<float>(h) }, TEMA::GetTexture("bleh")));

	
	SDL_QueryTexture(TEMA::GetTexture("NG"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("NG", new NewGameButton({ 0,0,w / 2 ,h }, { (float)WIDTH / 2 - w / 2 / 2,float(HEIGHT / 1.85 - h / 2) , (float)w / 2, (float)h }, TEMA::GetTexture("NG")));

	SDL_QueryTexture(TEMA::GetTexture("Play"), nullptr, nullptr, &w, &h);
	m_objects.emplace_back("no", new PlayButton({ 0,0,w / 2 ,h }, { (float)WIDTH / 2 - w / 2 / 2,float(HEIGHT / 1.85 - (h - 130) / 2 ), (float)w / 2, (float)h }, TEMA::GetTexture("Play")));
	m_objects.emplace_back("Exit", new ExitButton({ 0,0,w / 2 ,h }, { (float)WIDTH / 2 - w / 2 / 2,float(HEIGHT / 1.85 - (h - 260) / 2) , (float)w / 2, (float)h }, TEMA::GetTexture("Exit")));

	//Load and Play the music on the title screen
	SoundManager::Load("Aud/VisagerTreeLoop.mp3", "title", SOUND_MUSIC);
	SoundManager::PlayMusic("title", -1);
	SoundManager::SetMusicVolume(4);

	std::cout << "Entering TitleState..." << std::endl;
}	

void TitleState::Update()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
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
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	SOMA::Unload("title",SOUND_MUSIC);
	m_objects.clear();
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
