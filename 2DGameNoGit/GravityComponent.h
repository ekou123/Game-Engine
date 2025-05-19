#pragma once
#include "Component.h"
#include "PositionComponent.h"
#include "Actor.h"
#include "Constants.h"
#include "MapComponent.h"
#include "TileMap.h"
#include "Player.h"
#include <iostream>

class GravityComponent : public Component {
public:
    GravityComponent(float strength, float terminalVel = 1000.0f) : g(strength), vmax(terminalVel), vy(0.0f) {}

    void init() override {
		// Initialize the component
		std::cout << "GravityComponent initialized with g: " << g << " and vmax: " << vmax << std::endl;
        vy = 0.0f;
	}
    void update(float dt) override {
        if (!enabled) return;

        auto* pos = owner->getComponent<PositionComponent>();
        // 2) get map
        auto* mapComp = owner->getComponent<MapComponent>();
        if (!pos || !mapComp) return;

        TileMap* map = mapComp->getMap();
        if (!map) {
            std::cerr << "GravityComponent: No map found!" << std::endl;
            return;
        }


        // 3) integrate velocity
        vy = std::min(vy + g * dt, vmax);
        float newY = pos->y + vy * dt;

        // assume we already computed newY = pos->y + vy*dt

// 1) figure out which tile‐row your feet would land in
        float feetY = newY + PLAYER_HEIGHT;
        int tileRow = int(feetY) / TILE_SIZE;

        // 2) sample two points *just inside* the dirt tile, not on the boundary
        int leftX = int(pos->x + 1);                     // +1 so you’re > the left edge
        int rightX = int(pos->x + PLAYER_WIDTH - 1);      // -1 so you’re < right edge
        float sampleY = tileRow * TILE_SIZE + 1;          // +1 so you’re inside that row

        bool hitLeft = map->isSolidWorldPos(leftX, sampleY);
        bool hitRight = map->isSolidWorldPos(rightX, sampleY);

        if (vy > 0 && (hitLeft || hitRight)) {
            // you’re falling into dirt
            // snap your feet to sit on top of that tile
            pos->y = tileRow * TILE_SIZE - PLAYER_HEIGHT;
            vy = 0;
            onGround = true;
        }
        else {
            // no collision, commit the fall
            pos->y = newY;
            onGround = false;
        }
    }

    void setOwner(Actor* actor) {
		owner = actor;
	}

    Actor* getOwner() {
        return owner;
    }

    float getGravity() const {
		return g;
	}
private:
    float g = 9.8;
    float vmax;
    float vy;
    bool onGround = false;
};