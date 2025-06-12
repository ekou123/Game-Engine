#pragma once
#include "Action.h"
#include "GameObject.h"

class MoveAction : public Action
{
public:
	MoveAction() = default;
	~MoveAction() override = default;

	void execute(Engine* engine, const bool* keyState, Player* player) override;

	bool isTriggering(const bool* keyState) override;
	// Check if the action is complete
	bool isComplete() const;
	// Reset the action to its initial state
	void reset();


};
