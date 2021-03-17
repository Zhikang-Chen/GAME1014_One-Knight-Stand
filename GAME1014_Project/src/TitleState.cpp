// Begin TitleState
#include "TitleState.h"

#include "EndState.h"
#include "SoundManager.h"

TitleState::TitleState() {}

void TitleState::Enter()
{
	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/DotC-LgXoAMrpqi.png", "Background_1");
	int w, h;
	SDL_QueryTexture(TEMA::GetTexture("Background_1"), nullptr, nullptr, &w, &h);
	m_pBackground = new Background({ 0,0,(int)w,(int)h }, {0,0, (float)w*5, (float)h*5 }, TEMA::GetTexture("Background_1"));
	m_objects.emplace_back("Background", m_pBackground);
	
	m_pSubTitle = new Label("Minecraft",WIDTH / 20, HEIGHT / 7, "Insert sub title here", { 0,0,0,0 });
	m_objects.emplace_back("Subtitle", m_pSubTitle);
	
	m_pTitle = new Label("Genshi_font", WIDTH / 25, HEIGHT / 27, "One Knight Stand", { 0,0,0,0 });
	m_objects.emplace_back("Title", m_pTitle);

	something = new Label("Minecraft", WIDTH /25, HEIGHT - 50, "I made the button but you can still use 'n' because I am too lazy to remove it", { 0,0,0,0 });
	m_objects.emplace_back("idk", something);

	TEMA::RegisterTexture("../GAME1017_Template_W01/Img/p.png", "Play");
	SDL_QueryTexture(TEMA::GetTexture("Play"), nullptr, nullptr, &w, &h);
	b = new BoolButton({ 0,0,w/3,h }, { (float)WIDTH / 2 - w/3 / 2,(float)HEIGHT / 2 - h / 2 , (float)w/3, (float)h }, TEMA::GetTexture("Play"));
	//m_objects.emplace("no", b);
	m_objects.emplace_back("no", b);

	//m_titleBgm = Mix_LoadMUS("../GAME1017_Template_W01/Aud/VisagerTreeLoop.mp3");
	//Mix_PlayMusic(m_titleBgm, -1); // 0, 1-n, or -1 for infinite
	//Mix_VolumeMusic(30);
	
	//Load and Play the music on the title screen
	SoundManager::Load("Aud/VisagerTreeLoop.mp3", "title", SOUND_MUSIC );
	SoundManager::PlayMusic("title", -1);
	SoundManager::SetMusicVolume(4);
	
	std::cout << "Entering TitleState..." << std::endl;
}


void TitleState::Update()
{
	for (auto i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Update();
	
	if (EVMA::KeyPressed(SDL_SCANCODE_N) || b->GetChangeState())
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
	m_objects.clear();
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState
