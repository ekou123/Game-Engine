#pragma once
#include <unordered_map>
#include "Biome.h"
#include "DesertBiome.h"
#include "ForestBiome.h"
#include "PlainsBiome.h"
#include "TundraBiome.h"

class BiomeManager {
public:
    BiomeManager();
    ~BiomeManager();


    const Biome& getBiome(BiomeType b) const;

private:
    std::unordered_map<BiomeType, std::unique_ptr<Biome>> registry;
};
