#pragma once
#include "Camera.h"
#include "Chunk.h"
#include "ChunkCoord.h"
#include "Constants.h"
#include "Module.h"
#include "PlayerModule.h"


struct ChunkManagerModule : Module {
public:
    static ChunkManagerModule& getInstance() {
        static ChunkManagerModule inst;
        return inst;
    }


    bool init(Engine*);

    void update(Engine&, float);

    void render(Engine&) override;
    void shutdown(Engine&) override;

    void updateChunks(int playerX, int playerY);

    void generateChunk(Chunk& c);

private:
	Engine* engine = nullptr;
    int loadRadius;

    std::unordered_map<ChunkCoord, std::unique_ptr<Chunk>, ChunkHash> chunks;
};
