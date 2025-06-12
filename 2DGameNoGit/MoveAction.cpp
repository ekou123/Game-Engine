#include "MoveAction.h"

#include "BlockRegistryModule.h"
#include "PositionComponent.h"

void MoveAction::execute(Engine* engine, const bool* keyState, Player* player)
{
	PositionComponent* pos = player->getComponent<PositionComponent>();
	if (!pos)
	{
		std::cerr << "PositionComponent not found for player." << std::endl;
		return;
	}

	float leftX = pos->x - 1;
	float rightX = pos->x + 1;
	float sampleY = pos->y; // Sample one unit below the player

	BlockRegistryModule* brm = engine->getModule<BlockRegistryModule>();
	if (!brm)
	{
		std::cerr << "BlockRegistryModule not found." << std::endl;
		return;
	}


	bool hitLeft = brm->isSolidAt(float(leftX), sampleY);
	bool hitRight = brm->isSolidAt(float(rightX), sampleY);

	if (keyState[SDL_SCANCODE_A])
	{
		if (hitLeft)
		{
			std::cout << "Hit solid block on the left at (" << leftX << ", " << sampleY << ")." << std::endl;
			return; // Can't move left if there's a solid block
		}
		pos->x -= player->speed;
	}

	if (keyState[SDL_SCANCODE_D])
	{
		if (hitRight)
		{
			std::cout << "Hit solid block on the right at (" << rightX << ", " << sampleY << ")." << std::endl;
			return; // Can't move right if there's a solid block
		}
		pos->x += player->speed;
	}

	
	
}

bool MoveAction::isTriggering(const bool* keyState)
{
	return keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D];
}

bool MoveAction::isComplete() const
{
	return false;
}

void MoveAction::reset()
{
	// No state to reset for this action
}
