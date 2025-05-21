#include <iostream>
#include "GameObject.h"
#include "Engine.h"
#include "PositionComponent.h"
#include "Component.h"
#include "BlockRegistryModule.h"
#include "SpriteComponent.h"

void GameObject::update(float dt)
{
    for (auto& c : components)
        c->update(dt); // Ensure Component is fully defined
    render();
}

bool GameObject::init(Engine* engine, int posX, int posY)
{
	this->engine = engine;
    if (!engine)
    {
        std::cerr << "Engine is null. Cannot initialize " << filePath << " GameObject." << std::endl;
        return false;
	}

    addComponent<PositionComponent>();
    getComponent<PositionComponent>()->setPosition(posX, posY);

    //auto& type = BlockRegistryModule::getInstance().get(id);
    std::unordered_map<int, std::unique_ptr<GameObject>> gameObjects = BlockRegistryModule::getInstance().getAll();

    // or, if you prefer to get a reference:
    GameObject& obj = *gameObjects[id];
    SDL_Rect r = obj.srcRect;
    addComponent<SpriteComponent>(engine->renderer, r, filePath);
    return true;
}

void GameObject::render()
{
    SpriteComponent* spriteComponent = getComponent<SpriteComponent>();
    if (!spriteComponent)
    {
        std::cerr << "Cannot find sprite component on object.";
        return;
    }
}


