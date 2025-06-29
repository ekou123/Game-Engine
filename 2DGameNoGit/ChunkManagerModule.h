#pragma once
#include "Camera.h"
#include "Chunk.h"
#include "ChunkCoord.h"
#include "Constants.h"
#include "FastNoiseLite.h"
#include "Module.h"
#include "Engine.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <limits.h> // for INT_MAX


class BiomeManager;

struct ChunkManagerModule : Module {
public:
    ChunkManagerModule() = default;
    ~ChunkManagerModule() override = default;
    ChunkManagerModule(const ChunkManagerModule&) = delete;

    ChunkManagerModule& operator=(const ChunkManagerModule&) = delete;

    static ChunkManagerModule& getInstance() {
        static ChunkManagerModule inst;
        return inst;
    }

    // Module interface
    bool init(Engine* engine) override;
    void update(Engine& engine, float dt) override;
    void render(Engine* engine) override;
    void shutdown(Engine& engine) override;

    // Force an immediate load/unload around a world-pixel position
    void updateChunks(int playerX, int playerY);

    float getGroundHeight(int worldTileX);
    float fBm(int x);
    BiomeType pickBiomeForChunk(const ChunkCoord& coord);

    // Procedurally fill a brand-new chunk
    void generateChunk(Chunk& chunk);

    // Get the list of all chunk coords currently loaded
    std::vector<ChunkCoord> getLoadedChunks() const;

private:
    Engine* engine = nullptr;
    BiomeManager* biomeManager = nullptr;
    FastNoiseLite noise;
    FastNoiseLite biomeNoise;
    float maxTerrainHeight = MAP_TILES_Y / 2;
    int     loadRadius = 1;
    // Remember which chunk the player was in last frame:
    ChunkCoord lastPlayerChunk{ INT_MAX, INT_MAX };
    // The set of live chunks:
    std::unordered_map<ChunkCoord, std::unique_ptr<Chunk>, ChunkHash> chunks;
};
