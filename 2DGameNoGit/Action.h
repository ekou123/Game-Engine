#pragma once
#include "Player.h"

class Action {
	public:
	virtual ~Action() = default;
	// Execute the action
	virtual void execute(Player* player) = 0;
	// Check if the action is complete
	virtual bool isComplete() const = 0;
	// Reset the action to its initial state
	virtual void reset() = 0;
};
