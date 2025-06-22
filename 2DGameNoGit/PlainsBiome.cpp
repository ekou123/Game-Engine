#include "PlainsBiome.h"
#include "BlockRegistryModule.h"
#include "StoneBlock.h"
#include "Enemy.h"

void PlainsBiome::generateTerrain(Chunk& c, Engine* engine) const
{
    // use your height‐map code, then maybe add grass decals
        // exactly like your old generateChunk, but with grass instead of dirt

    BlockRegistryModule* blockRegistry = engine->getModule<BlockRegistryModule>();

    // use your height‐map code, then maybe add grass decals
    // exactly like your old generateChunk, but with grass instead of dirt
    // 1) Loop in *tile* coordinates
    for (int ty = 0; ty < CHUNK_SIZE; ++ty) {
        for (int tx = 0; tx < CHUNK_SIZE; ++tx) {
            // world‐tile coords of this location:
            int worldTileX = c.coord.x * CHUNK_SIZE + tx;
            int worldTileY = c.coord.y * CHUNK_SIZE + ty;

            // 2) Get the terrain height here, in *tiles*
            float groundHTiles = getGroundHeight(worldTileX);
            //float groundHTiles = fBm(worldTileX) * maxTerrainHeight;
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
                    block = std::make_unique<DirtBlock>(
                        engine,
                        px,
                        py,
                        TILE_DIRT
                    );
                }
                else
                {
                    block = std::make_unique<StoneBlock>(
                        engine,
                        px,
                        py,
                        TILE_STONE
                    );
                }


                blockRegistry->addBlock(std::move(block), c);
            }
            // else leave empty (air)
        }
    }
}
