#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include "Camera.h"

class Engine;
class BlockRegistryModule;

//const int TILE_SIZE = 32;
//const int MAP_WIDTH = 800;
//const int MAP_HEIGHT = 608;

class TileMap {
public:
	std::string name;

	TileMap(Engine* engine, float spawnX, float spawnY);

	bool init(Engine* engine, float spawnX, float spawnY);

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

