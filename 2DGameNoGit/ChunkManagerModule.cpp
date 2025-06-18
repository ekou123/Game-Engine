#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "Chunk.h"
#include "ChunkCoord.h"
#include "ChunkManagerModule.h"

#include "Biome.h"
#include "BiomeManager.h"
#include "PositionComponent.h"
#include "BlockRegistryModule.h"
#include "DirtBlock.h"
#include "FastNoiseLite.h"
#include "Player.h"
#include "SandBlock.h"
#include "StoneBlock.h"
#include "WaterBlock.h"

bool ChunkManagerModule::init(Engine* eng) {
    biomeNoise.SetSeed(424242);
    biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    biomeNoise.SetFrequency(0.002f);    // lower frequency → large biome blobs

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
            ptr->setBiome(pickBiomeForChunk(cc));
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

    BiomeType biomeType = pickBiomeForChunk(c.coord);
    const Biome& biome = biomeManager->getBiome(c.biomeType);
    biome.generateTerrain(c);

    
}

BiomeType ChunkManagerModule::pickBiomeForChunk(const ChunkCoord& cc) {
    // center of the chunk in *tiles*
    float worldX = float(cc.x * CHUNK_SIZE + CHUNK_SIZE / 2);
    float worldY = float(cc.y * CHUNK_SIZE + CHUNK_SIZE / 2);

    // FastNoiseLite will internally multiply by the 0.002 frequency you set
    float v = biomeNoise.GetNoise(worldX, worldY); // in [-1..+1]

    // normalize to [0..1]
    v = (v + 1.0f) * 0.5f;

    // map into [0 .. Count-1]
    int idx = int(v * float(int(BiomeType::Count)));
    if (idx >= int(BiomeType::Count)) idx = int(BiomeType::Count) - 1;

    return BiomeType(idx);
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
    float raw = noise.GetNoise(float(worldTileX), 0.0f);    // [-1..+1]
    float n = (raw + 1.0f) * 0.5f;                   // [0..1]

    // 2) bias curve (optional)
    n = pow(n, 1.2f);

    // 3) scale to [minH..maxH] in tiles
    constexpr float minH = 5;   // e.g. sea level at 5 tiles
    float     maxH = float(maxTerrainHeight);
    return n * (maxH - minH) + minH;
}


void ChunkManagerModule::render(Engine*) {
    // no per‐chunk rendering here; blocks are drawn by BlockRegistryModule
}

void ChunkManagerModule::shutdown(Engine&) {
    chunks.clear();
}

