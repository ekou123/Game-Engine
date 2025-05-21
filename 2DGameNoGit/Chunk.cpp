#include "Chunk.h"
#include "PerlinNoise.h"
#include "FastNoiseLite.h"


Chunk::Chunk(int cx_, int cy_)
    : cx(cx_), cy(cy_), tiles(CHUNK_SIZE* CHUNK_SIZE, TILE_EMPTY)
{
    generate();
}

void Chunk::generate() {
    // in Chunk::generate()
    float scale = 0.005f;    // “zoom” of the noise
    for (int y = 0; y < CHUNK_SIZE; ++y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            int worldX = cx * CHUNK_SIZE + x;
            int worldY = cy * CHUNK_SIZE + y;

            // sample fractal (fBm) height
            float h = 0;
            float amp = 1, freq = 1;
            for (int o = 0; o < 4; ++o) {
                h += amp * perlin.noise(worldX * freq * scale, worldY * freq * scale);
                amp *= 0.5f;
                freq *= 2.0f;
            }
            // normalize from roughly [–1,1] to [0,1]
            h = (h * 0.5f) + 0.5f;

            // choose tile by height
            int tile;
            /*if (h < 0.30f) tile = TILE_WATER;
            else if (h < 0.35f) tile = TILE_SAND;
            else if (h < 0.70f) tile = TILE_GRASS;
            else                tile = TILE_DIRT;*/
            if (h <=  0.40) {
                tile = TILE_DIRT;
                tiles[y * CHUNK_SIZE + x] = tile;

            }
            else {
                continue;
            }
            
        }
    }
}

//void Chunk::generate() {
//    // in Chunk::generate()
//    float scale = 0.005f;    // “zoom” of the noise
//    for (int y = 0; y < CHUNK_SIZE; ++y) {
//        for (int x = 0; x < CHUNK_SIZE; ++x) {
//            int worldX = cx * CHUNK_SIZE + x;
//            int worldY = cy * CHUNK_SIZE + y;
//
//            // sample fractal (fBm) height
//            float h = 0;
//            float amp = 1, freq = 1;
//            for (int o = 0; o < 4; ++o) {
//                h += amp * perlin.noise(worldX * freq * scale, worldY * freq * scale);
//                amp *= 0.5f;
//                freq *= 2.0f;
//            }
//            // normalize from roughly [–1,1] to [0,1]
//            h = (h * 0.5f) + 0.5f;
//
//            // choose tile by height
//            int tile;
//            /*if (h < 0.30f) tile = TILE_WATER;
//            else if (h < 0.35f) tile = TILE_SAND;
//            else if (h < 0.70f) tile = TILE_GRASS;
//            else                tile = TILE_DIRT;*/
//            if (h >= 0.70) tile = TILE_DIRT;
//
//            tiles[y * CHUNK_SIZE + x] = tile;
//        }
//    }
//}

PerlinNoise Chunk::perlin{ 2016U }; 

int Chunk::getTile(int localX, int localY) const {
    return tiles[localY * CHUNK_SIZE + localX];
}



