#pragma once
#include <iostream>
#include "State.h"
#include "StateMachine.h"



class NeutralState : public State {
public:
	NeutralState(Player* player, StateMachine* stateMachine)
		: State(player, stateMachine) {
		name = "Deez";
	};


	void enter() override {
		std::cout << "Entering Neutral State\n";
	}

	void handleInput(const bool* keystate, float dt) override;

	void update(float deltaTime) override {
		std::cout << "Updating Neutral State\n";
	}

	void exit() override {
		std::cout << "Exiting Neutral State\n";
	}
};
