#pragma once
#include "Engine.h"
#include "PositionComponent.h"

class Component;

struct GameObject
{
public:
    GameObject() = default;
    ~GameObject() = default;

    // disable copy so you don’t accidentally copy unique_ptr
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    // allow moves if you really need them
    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        // 1) make the component
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->setOwner(this);
        T* ptr = comp.get();

        // 2) move it into the vector
        components.emplace_back(std::move(comp));

        // 3) put pointer in lookup
        lookup[typeid(T)] = ptr;

        // 4) initialize
        ptr->init();
        return ptr;
    }

    template<typename T>
    T* getComponent() {
        auto it = lookup.find(typeid(T));
        if (it != lookup.end())
            return static_cast<T*>(it->second);
        return nullptr;
    }

    void update(float dt) {
        for (auto& c : components)
            c->update(dt);
    }

    bool init(Engine* engine, int posX, int posY)
    {
        addComponent<PositionComponent>();
		getComponent<PositionComponent>()->setPosition(posX, posY);
    }

private:
    std::vector<std::unique_ptr<Component>>          components;
    std::unordered_map<std::type_index, Component*>  lookup;
    int height, width;
};
