#pragma once
#include <vector>
#include "Constants.h"
#include "PerlinNoise.h"

struct Chunk {
	int cx, cy;
	std::vector<int> tiles;
	static PerlinNoise perlin;

	float h = perlin.noise(WORLD_TILES_X, WORLD_TILES_Y);

public:
	Chunk(int cx, int cy);
	void generate();
	int getTile(int localX, int localY) const;
};