#include "MoveLeftAction.h"

#include "PositionComponent.h"

void MoveLeftAction::execute(Player* player)
{
	PositionComponent* pos = player->getComponent<PositionComponent>();
	if (!pos)
	{
		std::cerr << "PositionComponent not found for player." << std::endl;
		return;
	}

	pos->x -= player->speed;
	
}

bool MoveLeftAction::isComplete() const
{
	return false;
}

void MoveLeftAction::reset()
{
	// No state to reset for this action
}
