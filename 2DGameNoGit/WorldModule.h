#pragma once
#include <iostream>
#include "TileMap.h"
#include "BlockRegistryModule.h"
#include "Engine.h"
#include "Module.h"

class TileMap;
class BlockRegistryModule;
class Engine;

struct WorldModule : Module {
    TileMap* tileSet = nullptr;

    Camera* camera = nullptr;

    void setCamera(Camera* cam) {
		camera = cam;
	}

    bool init(Engine*);
    void update(Engine&, float);

    void render(Engine& E);
        
    
    void shutdown(Engine&);
};