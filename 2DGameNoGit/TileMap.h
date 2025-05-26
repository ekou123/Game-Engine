#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <iostream>

#include "BlockRegistryModule.h"
#include "Camera.h"

//const int TILE_SIZE = 32;
//const int MAP_WIDTH = 800;
//const int MAP_HEIGHT = 608;

class ChunkManager;
class Engine;

class TileMap {
public:
	
	TileMap(Engine* engine, float spawnX, float spawnY);


	std::string name;

	void render(SDL_Renderer* renderer, const Camera& camera);

	void update(float playerX, float playerY);

	bool isSolidWorldPos(float worldX, float worldY) const;

	void setRegistry(BlockRegistryModule* registry) {
		blockRegistry = registry;
	}

private:
	std::vector<std::vector<int>> map;
	BlockRegistryModule* blockRegistry = nullptr;
};

