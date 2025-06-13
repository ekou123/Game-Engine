#pragma once
#include <iostream>

#include "TileMap.h"

class Engine;

struct Module {
	virtual ~Module() = default;

	static Module& getInstance() {
		static Module instance;
		return instance;
	};

	//Called once after SDL is up but before run()
	virtual bool init(Engine* engine) { return true; }
	// Called each frame before render()
	virtual void update(Engine& engine, float dt) {}
	// Called each frame after update()
	virtual void render(Engine* engine) {}
	// Called on Shutdown
	virtual void shutdown(Engine& engine) {}
};