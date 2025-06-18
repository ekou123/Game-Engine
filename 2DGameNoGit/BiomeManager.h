#pragma once
#include <unordered_map>
#include "Biome.h"
#include "DesertBiome.h"
#include "PlainsBiome.h"

class BiomeManager {
public:
    BiomeManager() {
        registry[BiomeType::Plains] = std::make_unique<PlainsBiome>();
        registry[BiomeType::Desert] = std::make_unique<DesertBiome>();
        // …etc…
    }

    const Biome& getBiome(BiomeType b) const {
        return *registry.at(b);
    }

private:
    std::unordered_map<BiomeType, std::unique_ptr<Biome>> registry;
};
