#include "Engine.h"

bool WorldModule::init(Engine* engine)
{
    // register blocks once
    auto& R = BlockRegistryModule::getInstance();
    /*R.registerBlock({ 0,"empty",false,{0,0,TILE_SIZE,TILE_SIZE} });
    R.registerBlock({ 1,"dirt", true,{1 * TILE_SIZE,0,TILE_SIZE,TILE_SIZE} });*/
    if (!tileSet)
    {
        tileSet = engine->getTileMap();
    }


    return true;
}

void WorldModule::render(Engine& E)
{
    // acquire camera from another module or global; for now assume it's at index 0

    if (!camera) {
        std::cout << "WorldModule cannot render. No Camera found" << std::endl;
        return;
    }

    if (!tileSet) {
        std::cout << "WorldModule cannot render. No TileMap found" << std::endl;
        return;
    }


    tileSet->render(E.renderer, *camera);
}
