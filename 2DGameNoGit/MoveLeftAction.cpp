#include "MoveLeftAction.h"

#include "PositionComponent.h"

void MoveLeftAction::execute(const bool* keyState, Player* player)
{
	PositionComponent* pos = player->getComponent<PositionComponent>();
	if (!pos)
	{
		std::cerr << "PositionComponent not found for player." << std::endl;
		return;
	}

	if (keyState[SDL_SCANCODE_A])
	{
		pos->x -= player->speed;
	}

	if (keyState[SDL_SCANCODE_D])
	{
		pos->x += player->speed;
	}

	
	
}

bool MoveLeftAction::isTriggering(const bool* keyState)
{
	return keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D];
}

bool MoveLeftAction::isComplete() const
{
	return false;
}

void MoveLeftAction::reset()
{
	// No state to reset for this action
}
