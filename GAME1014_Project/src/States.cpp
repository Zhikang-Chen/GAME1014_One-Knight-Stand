#include "States.h"
#include "StateManager.h" // Make sure this is NOT in "States.h" or circular reference.
#include "Engine.h"

// Begin State. CTRL+M+H and CTRL+M+U to turn on/off collapsed code.
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}
void State::Resume() {}


GameObject* State::FindObject(std::string id)
{
	for (const auto& object : m_objects)
	{
		if (object.first == id)
		{
			return(object.second);
		}
	}
	cout << id << " Not found" << endl;
}
// End State.