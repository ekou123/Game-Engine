#pragma once
#include "Action.h"
#include "GameObject.h"

class MoveLeftAction : public Action
{
public:
	MoveLeftAction() = default;
	~MoveLeftAction() override = default;

	void execute(Player* player) override;
	// Check if the action is complete
	bool isComplete() const;
	// Reset the action to its initial state
	void reset();


};
