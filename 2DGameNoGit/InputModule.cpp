#include <iostream>
#include "InputModule.h"

#include "JumpAction.h"
#include "MoveAction.h"
#include "PlayerModule.h"

bool InputModule::init(Engine* engine) {
	auto moveAction = std::make_shared<MoveAction>();
	auto jumpAction = std::make_shared<JumpAction>();

	bindKey(moveAction);
	bindKey(jumpAction);
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

	for (auto& action : keyBindings) {
		if (action->isTriggering(keys)) {
			PlayerModule* pm = engine.getModule<PlayerModule>();
			action->execute(&engine, keys, pm->getPlayer());
		} else if (!action->isComplete()) {
			action->reset();
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


void InputModule::bindKey(std::shared_ptr<Action> action) {
	keyBindings.push_back(action);
	allActions.push_back(action);
}
