#include "CameraModule.h"
#include "Engine.h"
#include "PlayerModule.h"
#include "Player.h"
#include "PositionComponent.h"
#include "Camera.h"
#include <iostream>

bool CameraModule::init(Engine* E) {
    Camera& camera = cam;
    // center on player


    PositionComponent* posComp = playerModule->getPlayer()->getComponent<PositionComponent>();
    if (!posComp) {
        std::cerr << "[CameraModule] Cannot find player position component.\n";
        return false;
    }

    float playerX = posComp->x,
        playerY = posComp->y;

    camera.x = playerX + Player::WIDTH / 2.0f - WINDOW_W / 2.0f;
    camera.y = playerY + Player::HEIGHT / 2.0f - WINDOW_H / 2.0f;
    // clamp...
    //camera.x = 0;
    //camera.y = 0;

    /*camera.x = std::clamp(camera.x, 0.0f, maxX);
    camera.y = std::clamp(camera.y, 0.0f, maxY);*/

    return true;
}

void CameraModule::update(Engine&, float) {
    Camera& camera = cam;
    // center on player


    PositionComponent* posComp = playerModule->getPlayer()->getComponent<PositionComponent>();
    if (!posComp) {
        std::cerr << "[CameraModule] Cannot find player position component.\n";
        return;
    }

    //std::cerr << "X: " << posComp->x << "Y: " << posComp->y << std::endl;



    float playerX = posComp->x,
        playerY = posComp->y;

    camera.x = playerX + Player::WIDTH / 2.0f - WINDOW_W / 2.0f;
    camera.y = playerY + Player::HEIGHT / 2.0f - WINDOW_H / 2.0f;
    // clamp...
}

void CameraModule::render(Engine* E) {
}

void CameraModule::shutdown(Engine&)
{
	
}
