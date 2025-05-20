#include "Chunk.h"
#include "ChunkManager.h"
#include "ChunkKey.h"
#include "ChunkKeyHasher.h"
#include "Constants.h"
#include "TileMap.h"
#include <unordered_map>

#include "Block.h"
#include <unordered_set>


Chunk& ChunkManager::getChunk(int cx, int cy) {
    ChunkKey key{ cx,cy };
    auto it = chunks.find(key);                  // only one argument!
    if (it == chunks.end())
        it = chunks.emplace(key, Chunk(cx, cy)).first;
    return it->second;
}

    // fetch tile at world‐pixel pos
int ChunkManager::getTileAt(float worldX, float worldY) {
        int tileX = int(worldX) / TILE_SIZE;
        int tileY = int(worldY) / TILE_SIZE;
        int cx = (tileX >= 0 ? tileX : tileX - CHUNK_SIZE + 1) / CHUNK_SIZE;
        int cy = (tileY >= 0 ? tileY : tileY - CHUNK_SIZE + 1) / CHUNK_SIZE;

        Chunk& ch = getChunk(cx, cy);
        int localX = tileX - cx * CHUNK_SIZE;
        int localY = tileY - cy * CHUNK_SIZE;
        return ch.getTile(localX, localY);
    }

    // ensure all chunks in a radius around player are loaded
/*void ChunkManager::updateAroundPlayer(float playerWorldX, float playerWorldY, int radiusChunks) {
    int pcx = int(playerWorldX) / PIXELS_PER_CHUNK;
    int pcy = int(playerWorldY) / PIXELS_PER_CHUNK;

    for (int dy = -radiusChunks; dy <= radiusChunks; ++dy) {
        for (int dx = -radiusChunks; dx <= radiusChunks; ++dx) {
            getChunk(pcx + dx, pcy + dy);
        }
    }

        // (Optional) unload distant chunks here to free memory
}*/

void ChunkManager::updateAroundPlayer(float playerX,
    float playerY,
    int radiusChunks)
{
    // 1) determine the new set of keys that should be loaded
    std::unordered_set<ChunkKey, ChunkKeyHasher> newKeys;
    int pcx = int(playerX) / PIXELS_PER_CHUNK;
    int pcy = int(playerY) / PIXELS_PER_CHUNK;
    for (int dy = -radiusChunks; dy <= radiusChunks; ++dy) {
        for (int dx = -radiusChunks; dx <= radiusChunks; ++dx) {
            newKeys.insert({ pcx + dx,pcy + dy });
        }
    }

    // 2) unload any chunks that are in loadedKeys but not in newKeys
    for (auto it = loadedKeys.begin(); it != loadedKeys.end(); ) {
        if (newKeys.count(*it) == 0) {
            // remove all block GameObjects for that chunk
            auto& actors = chunkActors[*it];
            /*for (auto* gameObject : actors) { READD THIS FOR LOOP IN FUTURE
                engine->removeGameObject(gameObject);
            }*/
            chunkActors.erase(*it);
            // optional: also erase the raw chunk data
            chunks.erase(*it);
            it = loadedKeys.erase(it);
        }
        else {
            ++it;
        }
    }

    // 3) load any new chunks and spawn their blocks
    for (auto const& key : newKeys) {
        if (loadedKeys.count(key) == 0) {
            // generate the chunk (or fetch if already generated)
            Chunk& chunk = getChunk(key.cx, key.cy);

            // spawn GameObjects for each non‐empty tile
            std::vector<GameObject*> actors;
            for (int y = 0; y < CHUNK_SIZE; ++y) {
                for (int x = 0; x < CHUNK_SIZE; ++x) {
                    int tileID = chunk.getTile(x, y);
                    if (tileID == TILE_EMPTY) continue;

                    float worldX = (key.cx * CHUNK_SIZE + x) * TILE_SIZE;
                    float worldY = (key.cy * CHUNK_SIZE + y) * TILE_SIZE;
                    // create a block object at that position
                    Block* b = new Block(engine,
                        int(worldX),
                        int(worldY),
                        tileID);
                    engine->addGameObject(b);
                    actors.push_back(b);
                }
            }

            // remember we’ve loaded this chunk
            chunkActors[key] = std::move(actors);
            loadedKeys.insert(key);
        }
    }
}

using ChunkMap = std::unordered_map<ChunkKey, Chunk, ChunkKeyHasher>;