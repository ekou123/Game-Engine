#include "BlockRegistryModule.h"
#include "Constants.h"
#include "DirtBlock.h"
#include "PositionComponent.h"

void BlockRegistryModule::addBlock(std::unique_ptr<GameObject> gameObject)
{
	//std::cerr << "Adding block to world\n";

	GameObject* gameObjectPtr = gameObject.get();
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

void BlockRegistryModule::registerBlock(int id, std::unique_ptr<GameObject> gameObject)
{
	//std::cerr << " Registering Block.\n";


	if (gameObjects.count(id)) {
		std::cerr << "GameObject with ID " << id
			<< " already exists. Overwriting.\n";
	}
	// move the unique_ptr into the map

	gameObjects.emplace(id, std::move(gameObject));
	order.push_back(id);
}


bool BlockRegistryModule::init(Engine* engine)
{
	std::cerr << "Initializing BlockRegistryModule\n";
	// Register blocks
	auto dirt = std::make_unique<DirtBlock>(engine, 0, 0, nextID);
	registerBlock(0, std::move(dirt));
	return true; // Initialization successful
}

void BlockRegistryModule::update(Engine& engine, float dt)
{
	
}

void BlockRegistryModule::render(Engine& engine)
{
}

void BlockRegistryModule::shutdown(Engine& engine)
{
}