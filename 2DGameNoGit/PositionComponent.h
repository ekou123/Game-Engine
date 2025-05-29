#pragma once
#include "Component.h"
#include <cmath>
#include "Constants.h" // Assuming TILE_SIZE is defined in Constants.h

class PositionComponent : public Component {
public:
    float x = 0, y = 0;

    void setPosition (float newX, float newY)
    {
		// std::cerr << "PositionComponent::setPosition called with x: " << newX << ", y: " << newY << std::endl;
		x = newX;
		y = newY;
    }

    void setTilePosition(float rawX, float rawY) {
        auto tx = std::floor(rawX / TILE_SIZE);
        auto ty = std::floor(rawY / TILE_SIZE);
        x = tx * TILE_SIZE;
        y = ty * TILE_SIZE;
    }
};