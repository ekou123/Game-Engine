#include "JumpAction.h"
#include "BlockRegistryModule.h"
#include "GravityComponent.h"
#include "MoveAction.h"
#include "PositionComponent.h"

void JumpAction::execute(Engine* engine, const bool* keyState, Player* player)
{
	std::cerr << "Executing JumpAction" << std::endl;
	if (!keyState[SDL_SCANCODE_SPACE]) return;

	std::cerr << "JumpAction triggered" << std::endl;

	PositionComponent* posComp = player->getComponent<PositionComponent>();
	if (!posComp)
	{
		std::cerr << "PositionComponent not found for player." << std::endl;
		return;
	}

	GravityComponent* gravComp = player->getComponent<GravityComponent>();
	if (!gravComp)
	{
		std::cerr << "GravityComponent not found for player." << std::endl;
		return;
	}

	if (gravComp->isOnGround())
	{
		std::cerr << "Player is on ground, applying jump force." << std::endl;
		// Apply jump force
		gravComp->applyForce(jumpForce);
		// Update position to prevent clipping into blocks
		done_ = true;
	}
}

bool JumpAction::isTriggering(const bool* keyState)
{
	return keyState[SDL_SCANCODE_SPACE];
}

bool JumpAction::isComplete() const
{
	return done_;
}

void JumpAction::reset()
{
	
}




