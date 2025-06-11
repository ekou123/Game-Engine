#pragma once
#include "Action.h"


class JumpAction : public Action
{
public:
	JumpAction() = default;
	~JumpAction() override = default;

	void execute(Engine* engine, const bool* keyState, Player* player) override;

	bool isTriggering(const bool* keyState) override;
	// Check if the action is complete
	bool isComplete() const;
	// Reset the action to its initial state
	void reset();

private:
	bool done_ = false;
	float jumpForce = 20.0f;

};
