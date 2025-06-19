#include "BiomeManager.h"

BiomeManager::BiomeManager() {
    registry[BiomeType::Plains] = std::make_unique<PlainsBiome>();
    registry[BiomeType::Desert] = std::make_unique<DesertBiome>();
    registry[BiomeType::Tundra] = std::make_unique<TundraBiome>();
    registry[BiomeType::Forest] = std::make_unique<ForestBiome>();
    
}

BiomeManager::~BiomeManager() = default;

const Biome& BiomeManager::getBiome(BiomeType type) const {
    auto it = registry.find(type);
    if (it != registry.end()) {
        return *(it->second);
    }
    throw std::runtime_error("Biome type not found");
}