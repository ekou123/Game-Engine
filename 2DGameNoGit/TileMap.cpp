#include <iostream>
#include "TileMap.h"
#include "BlockRegistryModule.h"
#include "SDL3/SDL.h"
#include "Constants.h"
#include "Block.h"
#include "Camera.h"
#include "DirtBlock.h"
#include "BlockType.h"

TileMap::TileMap(Engine* engine, float spawnX, float spawnY)
{
    // 1) initialize the ID grid
    map.assign(MAP_TILES_Y,
        std::vector<int>(MAP_TILES_X, TILE_EMPTY));

    // 2) compute the spawn tile coordinates
    int centerX = int(spawnX) / TILE_SIZE;
    int centerY = int(spawnY) / TILE_SIZE;

    const int radius = 10; // how many tiles in each direction
    for (int dy = -radius; dy <= radius; ++dy) {
        for (int dx = -radius; dx <= radius; ++dx) {
            int tx = centerX + dx;
            int ty = centerY + dy;
            if (tx < 0 || tx >= MAP_TILES_X ||
                ty < 0 || ty >= MAP_TILES_Y)
                continue;

            // set dirt in your map
            map[ty][tx] = TILE_DIRT;

            // convert tile coords back to world pos
            float wx = tx * TILE_SIZE;
            float wy = ty * TILE_SIZE;

            // spawn a Block GameObject for this tile:
            auto dirtBlock = std::make_unique<DirtBlock>(
                engine, int(wx), int(wy), TILE_DIRT
            );
            DirtBlock* raw = dirtBlock.get();
            BlockRegistryModule::getInstance().addBlock(std::move(dirtBlock));
            //tileActors.push_back(raw);
        }
    }
}

//void TileMap::render(SDL_Renderer* renderer,
//    SDL_Texture* tileTexture,
//    const Camera& camera)
//{
//    // which tile row/col the camera’s top‐left sits over
//    int startCol = camera.x / TILE_SIZE;
//    int startRow = camera.y / TILE_SIZE;
//
//    // how many tiles fit on the screen +1 for partial
//    int colsOnScreen = WINDOW_W / TILE_SIZE + 1;
//    int rowsOnScreen = WINDOW_H / TILE_SIZE + 1;
//
//    // clamp to map bounds
//    int endCol = std::min(startCol + colsOnScreen, MAP_TILES_X);
//    int endRow = std::min(startRow + rowsOnScreen, MAP_TILES_Y);
//    startCol = std::max(0, startCol);
//    startRow = std::max(0, startRow);
//
//    SDL_FRect destRect{ 0, 0, TILE_SIZE, TILE_SIZE };
//    SDL_FRect srcRect{ 0, 0, TILE_SIZE, TILE_SIZE };
//
//    for (int y = startRow; y < endRow; ++y) {
//        for (int x = startCol; x < endCol; ++x) {
//            int tileID = map[y][x];
//            if (tileID == TILE_EMPTY) continue;
//
//            srcRect.x = tileID * TILE_SIZE;
//            srcRect.y = 0;
//            destRect.x = x * TILE_SIZE - camera.x;
//            destRect.y = y * TILE_SIZE - camera.y;
//
//            SDL_RenderTexture(renderer, tileTexture, &srcRect, &destRect);
//        }
//    }
//}

/*void TileMap::render(Engine* engine, SDL_Renderer* renderer,
    SDL_Texture* tileTexture,
    const Camera& camera)
{
    //std::cout << "Chunk Manager: " << chunkManager << " wx: " << camera.x << " wy: " << camera.y << std::endl;
    // 1) compute which tiles the camera actually covers
    int startTileX = camera.x / TILE_SIZE;
    int startTileY = camera.y / TILE_SIZE;
    int endTileX = (camera.x + WINDOW_W) / TILE_SIZE + 1;
    int endTileY = (camera.y + WINDOW_H) / TILE_SIZE + 1;

    // 2) prepare your src/dest rects
    SDL_FRect srcRect{ 0, 0, TILE_SIZE, TILE_SIZE };
    SDL_FRect destRect{ 0, 0, TILE_SIZE, TILE_SIZE };

    // 3) loop *only* over visible tiles, pulling from ChunkManager
    for (int ty = startTileY; ty < endTileY; ++ty) {
        for (int tx = startTileX; tx < endTileX; ++tx) {
            float wx = tx * TILE_SIZE;
            float wy = ty * TILE_SIZE;

            int tileID = 0;
            if (tileID == TILE_EMPTY) continue;

            srcRect.x = tileID * TILE_SIZE;
            srcRect.y = 0;

            destRect.x = wx - camera.x;
            destRect.y = wy - camera.y;
            //SDL_RenderTexture(renderer, tileTexture, &srcRect, &destRect);
        }
    }
}*/

void TileMap::render(SDL_Renderer* renderer, const Camera& cam)
{
    for (auto& [id, ptr] : BlockRegistryModule::getInstance().getAll()) {
		ptr->render(renderer, cam);
	}
}

void TileMap::update(float playerX, float playerY) {
}

bool TileMap::isSolidWorldPos(float worldX, float worldY) const {
    int tileX = int(worldX) / TILE_SIZE;
    int tileY = int(worldY) / TILE_SIZE;

    //std::cout << "TileMap::isSolidWorldPos: tileX: " << tileX << " tileY: " << tileY << std::endl;

    // TRUE guard against *this* map’s dimensions:
    if (tileY < 0 ||
        tileY >= int(map.size()) ||      // no such row
        tileX < 0 ||
        tileX >= int(map[tileY].size()))  // no such column
    {
        return false;
    }

    /*//int id = map[tileY][tileX];
    if (std::move(BlockRegistryModule::getInstance().getAt(tileX, tileY))->isSolid())
    {
        return true;
    }
    else
    {
        return false;
    }*/
}
