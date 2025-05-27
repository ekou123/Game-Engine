#include "BlockRegistryModule.h"
#include "BlockType.h"
#include "Constants.h"
#include "DirtBlock.h"
#include "Engine.h"

void BlockRegistryModule::addBlock(std::unique_ptr<Block> gameObject)
{
	std::cerr << "Adding block to world\n";

	Block* gameObjectPtr = gameObject.get();
	PositionComponent* posComp = gameObjectPtr->getComponent<PositionComponent>();
	if (posComp == nullptr)
	{
		std::cerr << "GameObject " << " has no PositionComponent. Cannot add to world.\n";
		return;
	}

	int tileX = posComp->x;
	int tileY = posComp->y;

	auto key = std::make_pair(tileX, tileY);
	if (worldObjects.count(key)) {
		std::cerr << "GameObject at position (" << tileX << ", " << tileY
			<< ") already exists. Overwriting.\n";
	}

	worldObjects.emplace(key, std::move(gameObject));
	worldOrder.push_back(tileY * MAP_TILES_X + tileX);
}


bool BlockRegistryModule::init(Engine* engine)
{
	// Register blocks
	auto dirt = std::make_unique<DirtBlock>(engine, 0, 0, nextID);
	registerBlock(0, std::move(dirt));
	return true; // Initialization successful
}