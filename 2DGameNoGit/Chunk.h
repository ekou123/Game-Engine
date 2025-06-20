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
	std::vector<std::unique_ptr<GameObject>> blocks;

    void setBiome(BiomeType biome) {
		biomeType = biome;
    }

    void addBlock(std::unique_ptr<GameObject> block) {
        blocks.push_back(std::move(block)); // Transfer ownership to the chunk
	}

};

inline const char* toString(BiomeType b) {
    switch (b) {
    case BiomeType::Plains: return "Plains";
    case BiomeType::Desert: return "Desert";
    case BiomeType::Forest: return "Forest";
    case BiomeType::Tundra: return "Tundra";
    default:                return "Unknown";
    }
}

// 2) (Optional) overload operator<< so you can stream it directly:
inline std::ostream& operator<<(std::ostream& os, BiomeType b) {
    return os << toString(b);
}
