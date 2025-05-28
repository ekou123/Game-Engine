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

    bool init(Engine*) override;
    void update(Engine&, float) override;

    void render(Engine& E) override;
        
    
    void shutdown(Engine&) override;
};