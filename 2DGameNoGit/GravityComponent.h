#pragma once
#include "Component.h"
#include "PositionComponent.h"
#include "Actor.h"
#include "Constants.h"
#include "MapComponent.h"
#include "TileMap.h"
#include "Player.h"
#include <iostream>

#include "BlockRegistryModule.h"

class GravityComponent : public Component {
public:
    GravityComponent(float strength, float terminalVel = 1000.0f) : g(strength), vmax(terminalVel), vy(0.0f) {}

    void init(Engine* E) override {
		// Initialize the component
		std::cout << "GravityComponent initialized with g: " << g << " and vmax: " << vmax << std::endl;
		this->engine = E;
        vy = 0.0f;
        enabled = true;
	}
    void update(float dt) override {
        if (!enabled) return;

        // 1) Get position + map
        auto* pos = owner->getComponent<PositionComponent>();
        auto* mapComp = owner->getComponent<MapComponent>();
        if (!pos || !mapComp) return;
        TileMap* map = mapComp->getMap();
        if (!map) {
            std::cerr << "GravityComponent: No map found!\n";
            return;
        }

        // 2) Integrate velocity
        vy = std::min(vy + g * dt, vmax);
        float fallDist = vy * dt;
        float newY = pos->y + fallDist;

        // 3) Compute which tile‐row the feet would land in
        float feetY = newY + PLAYER_HEIGHT;
        int   tileRow = int(feetY) / TILE_SIZE;

        // 4) Compute clamp position (exact contact Y)
        float groundY = tileRow * TILE_SIZE;           // world‐Y of tile top
        float maxY = groundY - PLAYER_HEIGHT;       // highest pos->y before overlap

        // 5) Sample left/right feet to see if that tile is solid
        int   leftX = int(pos->x) + 1;
        int   rightX = int(pos->x + PLAYER_WIDTH) - 1;
        float sampleY = groundY + 1.0f;                // one pixel into that tile

        auto* brm = engine->getModule<BlockRegistryModule>();
        bool hitLeft = brm->isSolidAt(float(leftX), sampleY);
        bool hitRight = brm->isSolidAt(float(rightX), sampleY);

        std::cerr << "GravityComponent: feetY: " << feetY << ", tileRow: " << tileRow
                  << ", groundY: " << groundY << ", maxY: " << maxY
                  << ", leftX: " << leftX << ", rightX: " << rightX
			<< ", hitLeft: " << hitLeft << ", hitRight: " << hitRight << std::endl;

        // 6) Clamp or fall
        if (vy > 0 && newY > maxY && (hitLeft || hitRight)) {
            // collision this frame: land exactly on ground
            pos->y = maxY;
            vy = 0;
            onGround = true;
        }
        else {
            // no collision: free‐fall
            pos->y = newY;
            onGround = false;
        }
    }

	/*void update(float dt) override
    {
        auto* pos = owner->getComponent<PositionComponent>();
        if (!pos) {
            std::cerr << "GravityComponent: no PositionComponent on owner\n";
            return;
        }
        // accelerate downward
        vy += g * dt;
        // clamp to terminal velocity
        vy = std::min(vy, vmax);

        // move the position
        pos->y += vy * dt;
    }*/

    void setOwner(GameObject* gameObject) {
		owner = gameObject;
	}

    GameObject* getOwner() {
        return owner;
    }

    float getGravity() const {
		return g;
	}
private:
    float g = 9.8;
    float vmax;
    float vy = 0;
    bool onGround = false;
	Engine* engine = nullptr;
};
