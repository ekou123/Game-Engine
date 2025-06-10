#include <iostream>
#include "InputModule.h"

#include "MoveLeftAction.h"
#include "PlayerModule.h"

bool InputModule::init(Engine* engine) {
	auto moveLeft = std::make_shared<MoveLeftAction>();

	bindKey(SDL_SCANCODE_A, moveLeft);
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

void InputModule::render(Engine&)
{
	
}

void InputModule::shutdown(Engine& engine)
{
	// Cleanup logic can be added here if needed
}


void InputModule::bindKey(SDL_Scancode sc, std::shared_ptr<Action> action) {
	keyBindings[sc].push_back(action);
	allActions.push_back(action);
}
