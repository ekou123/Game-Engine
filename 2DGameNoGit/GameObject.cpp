#include "GameObject.h"

void GameObject::update(float dt)
{
    for (auto& c : components)
        c->update(dt); // Ensure Component is fully defined
    render();
}

bool GameObject::init(Engine* engine, int posX, int posY)
{
    addComponent<PositionComponent>();
    getComponent<PositionComponent>()->setPosition(posX, posY);
    return true;
}

void GameObject::render()
{
	
}


