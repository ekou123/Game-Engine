#include "BlockRegistryModule.h"
#include "Constants.h"
#include "DirtBlock.h"
#include "PositionComponent.h"
#include <iostream>

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
			addBlock(std::move(dirtBlock));
			//tileActors.push_back(raw);

		}
	}

	return true;
}

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


void BlockRegistryModule::update(Engine& engine, float dt)
{
}

void BlockRegistryModule::render(Engine& engine)
{
	if (worldObjects.empty()) {
		std::cerr << "World Objects empty\n";
		return;
	}

	// Each `objPtr` here is a non‐owning raw pointer from the unique_ptr,
	// so we know it’s still valid.
	for (auto& [coord, uptr] : worldObjects) {		
		if (uptr) {
			uptr.get()->render(engine.renderer, *engine.getCamera());
		}
		else {
			// In principle this shouldn’t happen if getAt() never moves them out,
			// but you can check anyway:
			std::cerr << "[render] encountered null unique_ptr at tile ("
				<< coord.first << "," << coord.second << ")\n";
		}
	}
}

bool BlockRegistryModule::isSolidAt(float worldX, float worldY)
{
	// 1) Convert the pixel‐space (worldX, worldY) to tile indices:
	int tileX = int(worldX) / TILE_SIZE;
	int tileY = int(worldY) / TILE_SIZE;

	// 2) Look up that tile in our worldObjects (we never move it out):
	GameObject* obj = getAt(tileX, tileY);
	if (!obj) {
		// No block here, so it’s not solid:
		std::cerr << "No object at (" << tileX << ", " << tileY << ")\n";
		std::cerr << "No Object at (" << worldX << ", " << worldY << " world | World Objects Size: " << worldObjects.size() << std::endl;
		return false;
	}

	// 3) If we found a block, ask if it’s solid:
	if (obj->isSolid()) {
		std::cerr << "Solid at (" << tileX << ", " << tileY << ")\n";
		return true;
	}
	else {
		return false;
	}
}

GameObject* BlockRegistryModule::getAt(int tileX, int tileY)
{
	auto key = std::make_pair(tileX, tileY);
	auto it = worldObjects.find(key);
	if (it == worldObjects.end()) {
		// Not found:
		//std::cerr << "Object not found at (" << tileX << ", " << tileY << " | World Objects Size: " << worldObjects.size() << std::endl;
		return nullptr;
	}
	// Return the raw pointer; do NOT move it out.
	return it->second.get();
}


void BlockRegistryModule::shutdown(Engine& engine)
{
}