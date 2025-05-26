#pragma once
#include "TileMap.h"

class Engine;

struct Module {
	virtual ~Module() = default;

	static Module& getInstance() {
		static Module instance;
		return instance;
	};

	//Called once after SDL is up but before run()
	bool init(Engine* engine);
	// Called each frame before render()
	void update(Engine& engine, float dt);
	// Called each frame after update()
	void render(Engine& engine);
	// Called on Shutdown
	void shutdown(Engine& engine);
};