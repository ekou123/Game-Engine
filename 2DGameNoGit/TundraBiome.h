#pragma once
#include "Biome.h"
#include "Constants.h"
#include "FastNoiseLite.h"
#include "SandBlock.h"
#include "StoneBlock.h"

class TundraBiome : public Biome {
public:
    TundraBiome() {
        // fill spawn table: e.g. 70% rabbits, 30% wolves
        /*spawnTable = {
          { EnemyType::Rabbit, 70 },
          { EnemyType::Wolf,   30 }
        };*/

        noise.SetSeed(1337);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFrequency(0.04f);
        noise.SetFractalOctaves(2);   // instead of 4 or 5
        maxTerrainHeight = -15;
    }

    void generateTerrain(Chunk& c, Engine* engine) const override;

    /*std::vector<EnemyType> spawnEnemies(std::mt19937& rng) const override {
        std::vector<EnemyType> out;
        std::uniform_int_distribution<int> dist(1, 100);
        for (int i = 0; i < MAX_ENEMIES_PER_CHUNK; ++i) {
            int roll = dist(rng);
            int sum = 0;
            for (auto [type, weight] : spawnTable) {
                sum += weight;
                if (roll <= sum) {
                    out.push_back(type);
                    break;
                }
            }
        }
        return out;
    }*/

private:
    // std::vector<std::pair<EnemyType, int>> spawnTable;
};
