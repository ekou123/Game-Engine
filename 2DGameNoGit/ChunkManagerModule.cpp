#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "Chunk.h"
#include "ChunkCoord.h"
#include "ChunkManagerModule.h"
#include "PositionComponent.h"
#include "BlockRegistryModule.h"
#include "DirtBlock.h"
#include "Player.h"

bool ChunkManagerModule::init(Engine* engine)
{
	this->engine = engine;
	loadRadius = 2;
	updateChunks(0, 0);
    return true;
}

void ChunkManagerModule::update(Engine&, float)
{
	
}

void ChunkManagerModule::render(Engine& E)
{
}
void ChunkManagerModule::shutdown(Engine&)
{
	
}

void ChunkManagerModule::updateChunks(int playerX, int playerY)
{
    int pcx = playerX / PIXELS_PER_CHUNK;
    int pcy = playerY / PIXELS_PER_CHUNK;

    // mark which coords should remain loaded:
    std::unordered_set<ChunkCoord, ChunkHash> want;
    for (int dy = -loadRadius; dy <= loadRadius; ++dy)
        for (int dx = -loadRadius; dx <= loadRadius; ++dx)
            want.insert({ pcx + dx, pcy + dy });

    // unload any chunk not in want:
    for (auto it = chunks.begin(); it != chunks.end(); ) {
        if (!want.count(it->first)) {
            it = chunks.erase(it);
        }
        else ++it;
    }

    // generate any new chunks:
    for (auto& cc : want) {
        if (!chunks.count(cc)) {
            chunks[cc] = std::make_unique<Chunk>();
            generateChunk(*chunks[cc]);
        }
    }
}

void ChunkManagerModule::generateChunk(Chunk& c)
{
    c.coord = c.coord;

    for (int y=0; y < CHUNK_SIZE; ++y)
    {
	    for (int x = 0; x < CHUNK_SIZE; ++x)
	    {
            float wx = (c.coord.x * CHUNK_SIZE + x) * TILE_SIZE;
            float wy = (c.coord.y * CHUNK_SIZE + y) * TILE_SIZE;

            auto dirt = std::make_unique<DirtBlock>(engine, int(wx), int(wy), TILE_DIRT);
			BlockRegistryModule* blockRegistry = engine->getModule<BlockRegistryModule>();
            if (!blockRegistry) {
				std::cerr << "[ChunkManagerModule] BlockRegistryModule not found!" << std::endl;
            }

            blockRegistry->addBlock(std::move(dirt));
	    }
    }
}

