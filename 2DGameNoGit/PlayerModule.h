#pragma once
#include "Module.h"
#include <iostream>
#include "TileMap.h"
#include "Constants.h"


// forward declare Engine so we can use Engine& in signatures
class Engine;
class Player;

struct PlayerModule : Module {
    Player* player = nullptr;
    TileMap* tileMap = nullptr;
    Camera* camera = nullptr;

    // **Declare** but do *not* define these in the header:
    bool   init(Engine* E);
    void   update(Engine& E, float dt);
    void   render(Engine& E);
    void   shutdown(Engine& E);

    // Wiring
    void setPlayer(Player* p) { player = p; }
    Player* getPlayer() { return player; }
    void setTileMap(TileMap* m) { tileMap = m; }
    void setCamera(Camera* c) { camera = c; }
};