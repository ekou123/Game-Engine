#include <iostream>
#include "InputModule.h"

#include "PlayerModule.h"

bool InputModule::init(Engine* engine) {
	// No Logic needed yet
	return true; // Initialization logic can be added here if needed
}

void InputModule::update(Engine& engine, float dt)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			engine.running = false;
		}
	}

	int numKeys;
	const bool* keys = SDL_GetKeyboardState(&numKeys);

	for (auto& [sc, actions] : keyBindings) {
		bool down = sc < numKeys && keys[sc];
		std::cerr << "Down: " << down << " for scancode: " << sc << std::endl;
		for (auto& act : actions)
		{
			if (down)
			{
				PlayerModule* pm = engine.getModule<PlayerModule>();
				act->execute(pm->getPlayer());
			} else if (!down && !act->isComplete())
			{
				act->reset();
			}
		}
	}
		
}
