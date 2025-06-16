#pragma once
#include "ChunkCoord.h"
#include "Constants.h"
#include "GameObject.h"

enum class BiomeType
{
    Plains,
    Desert,
    Forest,
    Tundra,
    Count
};

struct Chunk
{
	ChunkCoord coord;
    BiomeType biomeType;
	std::vector<GameObject*> blocks;

    void setBiome(BiomeType biome) {
		biomeType = biome;
    }

};
