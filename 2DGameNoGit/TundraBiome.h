#pragma once
#include "Biome.h"
#include "Constants.h"
#include "FastNoiseLite.h"

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
        noise.SetFrequency(0.05f);
    }

    void generateTerrain(Chunk& c, Engine* engine) const override {
        // use your height‐map code, then maybe add grass decals
        // exactly like your old generateChunk, but with grass instead of dirt
    }

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