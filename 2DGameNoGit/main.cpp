#include <algorithm>
#include"Constants.h"
#include "Player.h"
#include "Engine.h"
#include "WorldModule.h"
#include "PlayerModule.h"
#include "CameraModule.h"
#include "RenderModule.h"
#include "BlockRegistryModule.h"

// main.cpp (Game)

int main() {
    
    Engine* engine = new Engine();
    TileMap* tileMap = new TileMap(engine, 0, 0);
	engine->setTileMap(tileMap);

    auto worldMod = std::make_unique<WorldModule>();
    auto playerMod = std::make_unique<PlayerModule>();
    auto cameraMod = std::make_unique<CameraModule>();
    auto renderMod = std::make_unique<RenderModule>();
	auto blockRegistryMod = std::make_unique<BlockRegistryModule>();

    tileMap->setRegistry(blockRegistryMod.get());

    //Player player(WINDOW_W / 2.0f, WINDOW_H / 2.0f, worldMod->tileSet);
    Player player;

    // 1) Register the player with the PlayerModule
    playerMod->setPlayer(&player);
    player.setCurrentMap(tileMap);

    /*player.addComponent<PositionComponent>();
    player.addComponent<GravityComponent>(9.8f);
    player.addComponent<MapComponent>(worldMod->tileSet);
    player.getComponent<GravityComponent>()->setOwner(&player);*/


    // 1) Inject the *real* camera & player
    worldMod->setCamera(&cameraMod->cam);
    playerMod->setTileMap(tileMap);
    cameraMod->setPlayerModule(playerMod.get());

    // 2) **This is the critical line**: give RenderModule the WorldModule's map
    renderMod->setWorld(tileMap);
    renderMod->setPlayer(playerMod->getPlayer());
    renderMod->setCamera(&cameraMod->cam); 
    playerMod->setCamera(&cameraMod->cam); 


    playerMod->getPlayer()->setCamera(&cameraMod->cam);
    engine->registerPlayer(playerMod->getPlayer());
    
    


    // 3) Register in order
    engine->registerModule(std::move(worldMod));
    engine->registerModule(std::move(playerMod));
    engine->registerModule(std::move(cameraMod));
    engine->registerModule(std::move(renderMod));

    if (!engine->init("TerrariaEngine", WINDOW_W, WINDOW_H)) return 1;
    engine->run();
    engine->shutdown();
    return 0;
}
