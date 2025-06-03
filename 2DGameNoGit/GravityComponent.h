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

    void init() override {
		// Initialize the component
		std::cout << "GravityComponent initialized with g: " << g << " and vmax: " << vmax << std::endl;
        vy = 0.0f;
        enabled = true;
	}
    void update(float dt) override {
        if (!enabled) {
            return;
        }
        if (onGround) {
            // If you’re already on the ground, do nothing.
            return;
        }

        // (1) Grab owner’s position and map:
        auto* pos = owner->getComponent<PositionComponent>();
        auto* mapComp = owner->getComponent<MapComponent>();
        if (!pos || !mapComp) return;

        TileMap* map = mapComp->getMap();
        if (!map) {
            std::cerr << "GravityComponent: No map found!\n";
            return;
        }

        // (2) integrate vertical velocity
        vy = std::min(vy + g * dt, vmax);
        float newY = pos->y + vy * dt;

        //   newY is the candidate y‐position in pixel‐space.

        // (3) figure out which tile‐row the feet will land in:
        float feetY = newY + PLAYER_HEIGHT;       // pixel coordinate of bottom of player
        int tileRow = int(feetY) / TILE_SIZE;     // integer tile‐row index

        // (4) sample “just inside” the left/right edges of the player’s feet:
        //     — pos->x is pixel‐space; +1 px moves you inside the left edge,
        //       -1 on width keeps you inside right edge
        int leftX = int(pos->x) + 1;
        int rightX = int(pos->x + PLAYER_WIDTH) - 1;
        float sampleY = float(tileRow * TILE_SIZE + 1);  // one pixel inside the top of that tile

        std::cerr << "leftX=" << leftX
            << ", rightX=" << rightX
            << ", sampleY=" << sampleY
            << ", tileRow=" << tileRow
            << "\n";

        bool hitLeft = BlockRegistryModule::getInstance().isSolidAt(float(leftX), sampleY);
        bool hitRight = BlockRegistryModule::getInstance().isSolidAt(float(rightX), sampleY);

		//std::cerr << "hitLeft: " << hitLeft << ", hitRight: " << hitRight << "\n";

        // (5) If we’re falling (vy>0) and either left or right collides, snap to ground:
        if (vy > 0 && (hitLeft || hitRight)) {
            // snap y so bottom of player = top of that tileRow:
            pos->y = float(tileRow * TILE_SIZE) - PLAYER_HEIGHT;
            vy = 0;
            onGround = true;
        }
        else {
            // no collision → commit the fall
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
};
