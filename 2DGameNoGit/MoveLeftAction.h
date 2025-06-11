#pragma once
#include "Action.h"
#include "GameObject.h"

class MoveLeftAction : public Action
{
public:
	MoveLeftAction() = default;
	~MoveLeftAction() override = default;

	void execute(const bool* keyState, Player* player) override;

	bool isTriggering(const bool* keyState) override;
	// Check if the action is complete
	bool isComplete() const;
	// Reset the action to its initial state
	void reset();


};
