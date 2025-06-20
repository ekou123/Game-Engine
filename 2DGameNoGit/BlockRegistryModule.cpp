﻿#include "BlockRegistryModule.h"
#include "Constants.h"
#include "DirtBlock.h"
#include "PositionComponent.h"
#include <iostream>

bool BlockRegistryModule::init(Engine* engine)
{
	/*int spawnX = 0;
	int spawnY = 0;

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
	}*/

	return true;
}

void BlockRegistryModule::addBlock(std::unique_ptr<GameObject> blkPtr, Chunk& chunk)
{
	GameObject* blk = blkPtr.get();
	//std::cerr << "[addBlock] called with blk=" << blk << "\n";
	auto* pos = blk->getComponent<PositionComponent>();
	if (!pos) {
		std::cerr << "[addBlock] pos is null—no PositionComponent attached.\n";
		return;
	}
	int tileX = int(pos->x / TILE_SIZE);
	int tileY = int(pos->y / TILE_SIZE);
	auto key = std::make_pair(tileX, tileY);

	int cx = tileX / CHUNK_SIZE;
	int cy = tileY / CHUNK_SIZE;
	ChunkCoord cc{ cx, cy };

	worldObjects.emplace(key, std::move(blkPtr));
	chunkMap[cc].push_back(blk);

	visibleObjects.push_back(blk);
	//std::cerr << "[addBlock] now worldObjects.size() = " << worldObjects.size() << "\n";
}

const std::vector<GameObject*>&
BlockRegistryModule::getBlocksInChunk(const ChunkCoord& cc) const
{
	static const std::vector<GameObject*> empty;

	auto it = chunkMap.find(cc);
	if (it == chunkMap.end()) return empty;
	return it->second;
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

void BlockRegistryModule::render(Engine* engine)
{
	
	auto* cmm = engine->getModule<ChunkManagerModule>();
	if (!cmm)
	{
		std::cerr << "[BlockRegistryModule] No ChunkManagerModule found.\n";
		return;
	}

	const auto& loaded = cmm->getLoadedChunks();

	for (auto const& cc : loaded)
	{
		const auto& blocks = getBlocksInChunk(cc);
		/*std::cerr << "[BlockRegistryModule] Rendering chunk at ("
			 << ") with "
			<< blocks.size() << " blocks.\n";*/
		for (GameObject* blk : blocks)
		{
			if (blk)
			{
				blk->render(engine->renderer, *engine->getCamera());
			}
		}
	}

	// Each `objPtr` here is a non‐owning raw pointer from the unique_ptr,
	// so we know it’s still valid.
	/*for (auto& [coord, uptr] : worldObjects) {		
		if (uptr) {
			uptr.get()->render(engine.renderer, *engine.getCamera());
		}
		else {
			// In principle this shouldn’t happen if getAt() never moves them out,
			// but you can check anyway:
			std::cerr << "[render] encountered null unique_ptr at tile ("
				<< coord.first << "," << coord.second << ")\n";
		}
	}*/
}

void BlockRegistryModule::removeChunk(const ChunkCoord& cc)
{
	auto it = chunkMap.find(cc);
	if (it == chunkMap.end()) return;

	for (GameObject* blk  : it ->second)
	{
		auto vit = std::find(visibleObjects.begin(), visibleObjects.end(), blk);
		if (vit != visibleObjects.end()) {
			visibleObjects.erase(vit);
		}
		else {
			std::cerr << "[BlockRegistryModule] removeChunk: Block not found in visibleObjects.\n";
		}

		auto pos = blk->getComponent<PositionComponent>();
		int tx = int(pos->x / TILE_SIZE);
		int ty = int(pos->y / TILE_SIZE);
		worldObjects.erase({ tx, ty });
	}

	chunkMap.erase(it);
}


bool BlockRegistryModule::isSolidAt(float worldX, float worldY)
{
	if (worldObjects.empty()) {
		std::cerr << "[BlockRegistryModule] World Objects empty in isSolidAt\n";
		return false;
	}

	// 1) Convert the pixel‐space (worldX, worldY) to tile indices:
	int tileX = int(worldX) / TILE_SIZE;
	int tileY = int(worldY) / TILE_SIZE;

	// 2) Look up that tile in our worldObjects (we never move it out):

	GameObject* obj = getAt(tileX, tileY);
	if (!obj) {
		/*// No block here, so it’s not solid:
		std::cerr << "No object at (" << tileX << ", " << tileY << ")\n";
		std::cerr << "No Object at (" << worldX << ", " << worldY << " world | World Objects Size: " << worldObjects.size() << std::endl;*/
		return false;
	}

	// 3) If we found a block, ask if it’s solid:
	if (obj->isSolid()) {
		//9800std::cerr << "Solid at (" << tileX << ", " << tileY << ")\n";
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
		return nullptr;
	}
	// Return the raw pointer; do NOT move it out.
	return it->second.get();
}


void BlockRegistryModule::shutdown(Engine& engine)
{
}