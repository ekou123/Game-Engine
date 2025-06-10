#pragma once
#include <unordered_map>

#include "Action.h"
#include "Module.h"

struct InputModule : Module {

public:
    static InputModule& getInstance()
    {
       static InputModule instance;
	   return instance;
	}

    bool init(Engine*);

    void update(Engine&, float);

    void render(Engine&) override;
    void shutdown(Engine&) override;

    void bindKey(SDL_Scancode sc, std::shared_ptr<Action> action) {
		keyBindings[sc].push_back(action);
		allActions.push_back(action);
	}

    bool isPressed(Action* action) const;
	bool isJustPressed(Action* action) const;
	bool isJustReleased(Action* action) const;

private:
    InputModule() = default;
    ~InputModule() = default;
    InputModule(const InputModule&) = delete;
    InputModule& operator=(const InputModule&) = delete;

    // Map from SDL_Scancode → vector of Actions bound to it:
    std::unordered_map<SDL_Scancode, std::vector<std::shared_ptr<Action>>> keyBindings;

    std::vector<std::shared_ptr<Action>> allActions;
};


