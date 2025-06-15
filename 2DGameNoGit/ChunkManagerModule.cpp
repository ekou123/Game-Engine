#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "Chunk.h"
#include "ChunkCoord.h"
#include "ChunkManagerModule.h"
#include "PositionComponent.h"
#include "BlockRegistryModule.h"
#include "DirtBlock.h"
#include "FastNoiseLite.h"
#include "Player.h"

bool ChunkManagerModule::init(Engine* eng) {

    noise.SetSeed(1337);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(0.05f);

    engine = eng;
    loadRadius = 2;
    // Force the very first update() to load around (0,0):
    lastPlayerChunk = { INT_MAX, INT_MAX };
    return true;
}

void ChunkManagerModule::update(Engine& engine, float /*dt*/) {
    // 1) Find the player and their position
    auto* pm = engine.getModule<PlayerModule>();
    if (!pm) return;
    Player* player = pm->getPlayer();
    if (!player) return;
    auto* pos = player->getComponent<PositionComponent>();
    if (!pos) return;

    // 2) Compute the chunk coordinates the player currently occupies
    int pcx = int(pos->x) / PIXELS_PER_CHUNK;
    int pcy = int(pos->y) / PIXELS_PER_CHUNK;
    ChunkCoord current{ pcx, pcy };

    // 3) Only if the player has crossed into a new chunk, regenerate
    if (current.x != lastPlayerChunk.x || current.y != lastPlayerChunk.y) {
        lastPlayerChunk = current;
        updateChunks(int(pos->x), int(pos->y));
    }
}

void ChunkManagerModule::updateChunks(int playerX, int playerY) {
    int pcx = playerX / PIXELS_PER_CHUNK;
    int pcy = playerY / PIXELS_PER_CHUNK;

    // 1) Build the set of chunk‐coords we want to keep
    std::unordered_set<ChunkCoord, ChunkHash> want;
    for (int dy = -loadRadius; dy <= loadRadius; ++dy) {
        for (int dx = -loadRadius; dx <= loadRadius; ++dx) {
            want.insert({ pcx + dx, pcy + dy });
        }
    }

	BlockRegistryModule* blockRegistry = engine->getModule<BlockRegistryModule>();
    if (!blockRegistry) {
		std::cerr << "[ChunkManager] BlockRegistryModule not found!\n";
        return;
    }

    // 2) Unload any chunks not in 'want'
    for (auto it = chunks.begin(); it != chunks.end(); ) {
        if (!want.count(it->first)) {
            // Remove all blocks in that chunk from the registry
            blockRegistry->removeChunk(it->first);
            // Erase the chunk itself
            it = chunks.erase(it);
        }
        else {
            ++it;
        }
    }

    // 3) Generate any brand‐new chunks we now want
    for (auto const& cc : want) {
        if (!chunks.count(cc)) {
            auto ptr = std::make_unique<Chunk>();
            ptr->coord = cc;
            generateChunk(*ptr);
            chunks.emplace(cc, std::move(ptr));
        }
    }
}

void ChunkManagerModule::generateChunk(Chunk& c) {
    auto* blockRegistry = engine->getModule<BlockRegistryModule>();
    if (!blockRegistry) {
        std::cerr << "[ChunkManager] BlockRegistryModule not found!\n";
        return;
    }

    // 1) Loop in *tile* coordinates
    for (int ty = 0; ty < CHUNK_SIZE; ++ty) {
        for (int tx = 0; tx < CHUNK_SIZE; ++tx) {
            // world‐tile coords of this location:
            int worldTileX = c.coord.x * CHUNK_SIZE + tx;
            int worldTileY = c.coord.y * CHUNK_SIZE + ty;

            // 2) Get the terrain height here, in *tiles*
            float groundHTiles = getGroundHeight(worldTileX);

            // 3) If our tile‐Y is BELOW that height, spawn a block:
            if (worldTileY >= int(groundHTiles)) {
                // now convert *tile*→*pixel* once:
                int px = worldTileX * TILE_SIZE;
                int py = worldTileY * TILE_SIZE;

                auto dirt = std::make_unique<DirtBlock>(
                    engine,
                    px,
                    py,
                    TILE_DIRT
                );
                blockRegistry->addBlock(std::move(dirt));
            }
            // else leave empty (air)
        }
    }
}

float ChunkManagerModule::fBm(int x)
{
    float total = 0, freq = 100, amp = 100, maxA = 100;
    for (int o = 0; o < 4; ++o)
    {
        total += noise.GetNoise(x * freq, 0.f) * amp;
		maxA += amp;
		amp *= 0.5f; // Decrease amplitude
		freq *= 2.0f; // Increase frequency
    }
    return total / maxA;
}


std::vector<ChunkCoord> ChunkManagerModule::getLoadedChunks() const {
    std::vector<ChunkCoord> out;
    out.reserve(chunks.size());
    for (auto const& kv : chunks) {
        out.push_back(kv.first);
    }
    return out;
}

float ChunkManagerModule::getGroundHeight(int worldTileX)
{
    float n = noise.GetNoise(float(worldTileX), 0.0f);

	n = (n + 1.0f) * 0.5f; // Normalize to [0, 1]

    return n * maxTerrainHeight;
}


void ChunkManagerModule::render(Engine*) {
    // no per‐chunk rendering here; blocks are drawn by BlockRegistryModule
}

void ChunkManagerModule::shutdown(Engine&) {
    chunks.clear();
}

