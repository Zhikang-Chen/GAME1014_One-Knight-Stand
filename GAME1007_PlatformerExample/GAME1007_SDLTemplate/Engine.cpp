#include "Engine.h"


int Engine::Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	cout << "Initializing engine..." << endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // If initialization is okay...
	{
		// Create the SDL window...
		cout << "First pass." << endl;
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (m_pWindow != nullptr)
		{
			// Create the SDL renderer...(back buffer)
			cout << "Second pass." << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, NULL);
			if (m_pRenderer != nullptr)
			{
				// Initialize subsystems later...
				cout << "Third pass." << endl;
			}
			else return false; // Renderer creation failed.
		}
		else return false; // Window creation failed.
	}
	else return false; // initalization failed.
	m_fps = (Uint32)round(1.0 / (double)FPS * 1000); // Converts FPS into milliseconds, e.g. 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);
	m_player.Init(m_pRenderer);
	cout << "Initialization successful!" << endl;
	m_running = true;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;

		case SDL_KEYDOWN:
			//Player jump
			if (event.key.keysym.sym == ' ' && m_player.IsGrounded()) //The player may only jump again if they are on the ground
			{
				m_player.SetAccelY(-60.0); //<- JUMPFORCE
				m_player.SetGrounded(false);
			}
				break;
			
		}
	}
}

bool Engine::KeyDown(const SDL_Scancode c)
{
	if (m_keystates[c] == 1)
	{
		return true;
	}
	else return false;
}

void Engine::CheckCollision()
{
	//Collision for Platforms
	for (int i = 0; i < 5; i++)
	{
		if (SDL_HasIntersection(&m_player.GetRect(), &m_platforms[i]))
		{
			
			if ((m_player.GetRect().y + m_player.GetRect().h) - (float)m_player.GetVelY() <= m_platforms[i].y)
			{//Collliding with the top side of the platform
				m_player.SetGrounded(true);
				m_player.StopY();
				m_player.SetY(m_platforms[i].y - m_player.GetRect().h);
			}
			else if (m_player.GetRect().y - (float)m_player.GetVelY() >= (m_platforms[i].y + m_platforms[i].h))

			{//Collliding with the bottom side of the platform
				m_player.StopY();
				m_player.SetY(m_platforms[i].y + m_platforms[i].h);
			}

			else if ((m_player.GetRect().x + m_player.GetRect().w) - (float)m_player.GetVelX() <= m_platforms[i].x)
			{//Collliding with the left side of the platform
				m_player.StopX();
				m_player.SetX(m_platforms[i].x - m_player.GetRect().w);
			}

			else if (m_player.GetRect().x - (float)m_player.GetVelX() >= (m_platforms[i].x + m_platforms[i].w))
			{//Collliding with the right side of the platform
				m_player.StopX();
				m_player.SetX(m_platforms[i].x + m_platforms[i].w);
			}
			
			
		}
	}
}

void Engine::Update()
{
	if (KeyDown(SDL_SCANCODE_A)) //Player Moving Left
		m_player.SetAccelX(-1.0);
	else if (KeyDown(SDL_SCANCODE_D)) //Player moving right
		m_player.SetAccelX(1.0);

	//Wrap the player
	if (m_player.GetRect().x < -51.0) m_player.SetX(1024.0);
	else if (m_player.GetRect().x > 1024.0) m_player.SetX(-50.0);

	//Update the player
	m_player.Update();
	CheckCollision();

	//If the player falls down a pit, lock controls.
	if (m_player.GetRect().y > HEIGHT)
	{
		m_player.Stop();
		m_player.SetAlive(false);
	}
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 64, 128, 255, 255);
	SDL_RenderClear(m_pRenderer);
	// Any drawing here...
	//Render platforms...
	SDL_SetRenderDrawColor(m_pRenderer, 192, 64, 0, 255);

	//DRAW the platforms
	for (int i =0; i < 5; i++)
	{
		SDL_RenderFillRect(m_pRenderer, &m_platforms[i]);
	}
	m_player.Render();

	if (m_player.GetAlive() == false)
	{
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
		SDL_RenderClear(m_pRenderer);
	}
	SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start; // 1055 - 1050 = 5ms
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);

}

int Engine::Run()
{
	if (m_running == true)
	{
		return 1;
	}
	// Start and run the "engine"
	if (Init("GAME1007 M1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL) == false)
	{
		return 2;
	}
	// We passed our initial checks, start the loop!
	while (m_running == true)
	{
		Wake();
		HandleEvents(); // Input
		Update();       // Processing
		Render();       // Output
		if (m_running == true)
			Sleep();
	}
	Clean();
	return 0;
}


void Engine::Clean()
{
	cout << "Cleaning engine..." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}


