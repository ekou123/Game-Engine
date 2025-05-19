#pragma once
#include "Component.h"

class PositionComponent : public Component {
public:
    float x = 0, y = 0;

    void setPosition (float newX, float newY)
    {
		x = newX;
		y = newY;
    }
};