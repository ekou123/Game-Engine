#pragma once
#include "Biome.h"
#include "Constants.h"
#include "FastNoiseLite.h"
#include "StoneBlock.h"
#include "SandBlock.h"

class DesertBiome : public Biome {
public:
    DesertBiome() {
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
        // 1) Loop in *tile* coordinates
        for (int ty = 0; ty < CHUNK_SIZE; ++ty) {
            for (int tx = 0; tx < CHUNK_SIZE; ++tx) {
                // world‐tile coords of this location:
                int worldTileX = c.coord.x * CHUNK_SIZE + tx;
                int worldTileY = c.coord.y * CHUNK_SIZE + ty;

                // 2) Get the terrain height here, in *tiles*
                //float groundHTiles = getGroundHeight(worldTileX);
                float groundHTiles = fBm(worldTileX) * maxTerrainHeight;
                // 3) If our tile‐Y is BELOW that height, spawn a block:
                if (worldTileY >= int(groundHTiles)) {
                    // now convert *tile*→*pixel* once:
                    int px = worldTileX * TILE_SIZE;
                    int py = worldTileY * TILE_SIZE;

                    float n = noise.GetNoise(worldTileX * 0.005f, worldTileY * 0.005f);
                    


                    std::cerr << "Biome Type: " << c.biomeType << std::endl;

                    std::unique_ptr<Block> block = nullptr;
                    if (n < 0.5f)
                    {
                        block = std::make_unique<SandBlock>(
                            engine,
                            px,
                            py,
                            TILE_DIRT
                        );
                    } else
                    {
                        block = std::make_unique<StoneBlock>(
                            engine,
                            px,
                            py,
                            TILE_STONE
                        );
                    }


                    //blockRegistry->addBlock(std::move(block));
                }
                // else leave empty (air)
            }
        }
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
