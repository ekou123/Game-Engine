#pragma once
#include "Module.h"
#include <iostream>
#include "PlayerModule.h"
#include "PositionComponent.h"
#include "Constants.h"

class Player;
class Engine;

struct CameraModule : Module {
    Camera cam{ 0,0,WINDOW_W,WINDOW_H };
    PlayerModule* playerModule = nullptr;

    bool init(Engine*);

    void update(Engine&, float);

    void render(Engine&);
    void shutdown(Engine&);

    void setPlayerModule(PlayerModule* p) { playerModule = p; }

    void setCamera(Camera* c) { cam = *c; }
};