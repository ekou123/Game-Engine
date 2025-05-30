#include "BlockRegistryModule.h"
#include "Constants.h"
#include "DirtBlock.h"
#include "PositionComponent.h"
#include <iostream>

void BlockRegistryModule::addBlock(GameObject* blk)
{
	
	auto* pos = blk->getComponent<PositionComponent>();
	if (!pos) {
		std::cerr << "Cannot add block without PositionComponent\n";
		return;
	}

	auto key = std::make_pair(int(pos->x / TILE_SIZE), int(pos->y / TILE_SIZE));
	worldObjects[key] = blk;
	worldOrder.push_back(key.second * MAP_TILES_X + key.first);

	std::cerr << "Added block at (" << key.first
		<< "," << key.second << ") to worldObjects | " << blk->name << std::endl;
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

	std::cerr << "Deez Nuts: " << worldObjects.find({ 5, 5 })->second << "\n";

	/*for (auto& [coord, obj] : worldObjects) {
		int tileX = coord.first;
		int tileY = coord.second;
		std::cerr << "Rendering block at " << tileX << "," << tileY << "\n";
		obj->render(engine.renderer, *engine.getCamera());
	}*/

	for (auto it = worldObjects.begin(); it != worldObjects.end(); ++it) {
		auto coord = it->first;       // std::pair<int,int>
		GameObject* obj = it->second; // raw pointer
		int tileX = coord.first;
		int tileY = coord.second;
		std::cerr << "Rendering block at " << tileX << "," << tileY << "\n";
		obj->render(engine.renderer, *engine.getCamera());
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