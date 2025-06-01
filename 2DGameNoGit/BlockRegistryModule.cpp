#include "BlockRegistryModule.h"
#include "Constants.h"
#include "DirtBlock.h"
#include "PositionComponent.h"
#include <iostream>

void BlockRegistryModule::addBlock(std::unique_ptr<GameObject> blkPtr)
{
	GameObject* blk = blkPtr.get();
	std::cerr << "[addBlock] called with blk=" << blk << "\n";
	auto* pos = blk->getComponent<PositionComponent>();
	if (!pos) {
		std::cerr << "[addBlock] pos is null—no PositionComponent attached.\n";
		return;
	}
	int tileX = int(pos->x / TILE_SIZE);
	int tileY = int(pos->y / TILE_SIZE);
	auto key = std::make_pair(tileX, tileY);
	worldObjects.emplace(key, std::move(blkPtr));
	std::cerr << "[addBlock] now worldObjects.size() = " << worldObjects.size() << "\n";
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
	int spawnX = 0;
	int spawnY = 0;
	// 1) initialize the ID grid
	map.assign(MAP_TILES_Y,
		std::vector<int>(MAP_TILES_X, TILE_EMPTY));

	// 2) compute the spawn tile coordinates
	int centerX = int(spawnX) / TILE_SIZE;
	int centerY = int(spawnY) / TILE_SIZE;

	const int radius = 10; // how many tiles in each direction
	for (int dy = -radius; dy <= radius; ++dy) {
		for (int dx = -radius; dx <= radius; ++dx) {
			int tx = centerX + dx;
			int ty = centerY + dy;
			if (tx < 0 || tx >= MAP_TILES_X ||
				ty < 0 || ty >= MAP_TILES_Y)
				continue;

			// set dirt in your map
			map[ty][tx] = TILE_DIRT;

			// convert tile coords back to world pos
			float wx = tx * TILE_SIZE;
			float wy = ty * TILE_SIZE;

			// spawn a Block GameObject for this tile:
			auto dirtBlock = std::make_unique<DirtBlock>(
				engine, int(wx), int(wy), TILE_DIRT
			);
			DirtBlock* raw = dirtBlock.get();
			if (!raw->getComponent<PositionComponent>())
			{
				std::cerr << "DirtBlock has no PositionComponent";
			}

			std::cerr << "Adding block at: " << raw->getComponent<PositionComponent>()->x << ", " << raw->getComponent<PositionComponent>()->y;
			addBlock(std::move(dirtBlock));
			//tileActors.push_back(raw);
		}
	}

	return true;
}

void BlockRegistryModule::update(Engine& engine, float dt)
{
}

void BlockRegistryModule::render(Engine& engine)
{
	//std::cerr << "worldObjects contains " << worldObjects.size() << " entries\n";
	if (worldObjects.size() <= 0)
	{
		std::cerr << "WorldObjects contains no entries";
		return;
	}


	//std::cerr << getAt(5,5) << "\n";

	for (auto& [coord, obj] : worldObjects) {
		int tileX = coord.first;
		int tileY = coord.second;
		//std::cerr << "Rendering block at " << tileX << "," << tileY << "\n";
		obj->render(engine.renderer, *engine.getCamera());
	}

	/*for (auto& kv : worldObjects) {
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
	}*/
}

std::unique_ptr<GameObject> BlockRegistryModule::getAt(int tileX, int tileY)
{
	auto key = std::make_pair(tileX, tileY);
	auto it = worldObjects.find(key);
	if (it == worldObjects.end()) {
		std::cerr << "GameObject at (" << tileX << ", " << tileY << ") not found.\n";
		return nullptr;
	}
	// “Move” the unique_ptr out of the map:
	std::unique_ptr<GameObject> result = std::move(it->second);
	return result;  // moved, not copied
}


void BlockRegistryModule::shutdown(Engine& engine)
{
}