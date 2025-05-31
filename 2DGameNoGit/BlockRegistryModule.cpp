#include "BlockRegistryModule.h"
#include "Constants.h"
#include "DirtBlock.h"
#include "PositionComponent.h"
#include <iostream>

void BlockRegistryModule::addBlock(GameObject* blk)
{
	if (!blk)
	{
		std::cerr << "Block is null ptr in BlockRegistryModule::addBlock";
		return;
	}
	
	auto* pos = blk->getComponent<PositionComponent>();
	if (!pos) {
		std::cerr << "Cannot add block without PositionComponent\n";
		return;
	}

	int tileX = int(pos->x / TILE_SIZE);
	int tileY = int(pos->y / TILE_SIZE);
	worldObjects.emplace(std::pair<int,int>(tileX,tileY), blk);
	//worldOrder.push_back(key.second * MAP_TILES_X + key.first);

	std::cerr << worldObjects.size() << " blocks in worldObjects\n";
}

void BlockRegistryModule::registerBlock(std::unique_ptr<GameObject> gameObject)
{
	//std::cerr << " Registering Block.\n";
	int id = nextID;


	if (gameObjects.count(id)) {
		std::cerr << "GameObject with ID " << id
			<< " already exists. Overwriting.\n";
	}
	// move the unique_ptr into the map

	gameObjects[id] = std::move(gameObject);
	order.push_back(id);
	nextID++;
}


bool BlockRegistryModule::init(Engine* engine)
{
	std::cerr << "Initializing BlockRegistryModule\n";
	// Register blocks
	//auto dirt = std::make_unique<DirtBlock>(engine, 0, 0, nextID);
	return true; // Initialization successful
}

void BlockRegistryModule::update(Engine& engine, float dt)
{
}

void BlockRegistryModule::render(Engine& engine)
{
	std::cerr << "worldObjects contains " << worldObjects.size() << " entries\n";


	std::cerr << getAt(5,5) << "\n";

	/*for (auto& [coord, obj] : worldObjects) {
		int tileX = coord.first;
		int tileY = coord.second;
		std::cerr << "Rendering block at " << tileX << "," << tileY << "\n";
		obj->render(engine.renderer, *engine.getCamera());
	}*/

	for (auto& kv : worldObjects) {
		int tileX = kv.first.first;
		int tileY = kv.first.second;
		GameObject* obj = kv.second;

		std::cerr << "Rendering block at " << tileX << "," << tileY << "\n";
		if (obj) {
			obj->render(engine.renderer, *engine.getCamera());
		} else {
			std::cerr << "Warning: GameObject at (" << tileX << ", " << tileY
				<< ") is null.\n";
		}
	}
}

const GameObject* BlockRegistryModule::getAt(int tileX, int tileY) const
{
	auto key = std::make_pair(tileX, tileY);
	auto it = worldObjects.find(key);

	if (it == worldObjects.end())
	{
		std::cerr << "GameObject at position (" << tileX << ", " << tileY
			<< ") not found.\n";
		return nullptr;
	}
	return it->second;
	//return worldObjects.find(id)
}


void BlockRegistryModule::shutdown(Engine& engine)
{
}