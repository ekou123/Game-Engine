#pragma once  
#include <iostream>

#include "BlockType.h"  
#include "Module.h"  
#include <unordered_map>  
#include <vector>

#include "GameObject.h"

class BlockRegistryModule : public Module {  
public:  
    static BlockRegistryModule& getInstance() {  
        static BlockRegistryModule instance;  
        return instance;  
    };  

    void registerBlock(std::unique_ptr<GameObject> gameObject) {
        int id = gameObject->getID();
        if (gameObjects.count(id)) {
            std::cerr << "GameObject with ID " << id
                << " already exists. Overwriting.\n";
        }
        // move the unique_ptr into the map
        gameObjects[id] = std::move(gameObject);
        order.push_back(id);
    }

    const std::unique_ptr<GameObject> & get(int id) const { return gameObjects.at(id); }

	const std::unordered_map<int, std::unique_ptr<GameObject>>& getAll() { return gameObjects; }

    const std::vector<int>& allIDs() const { return order; }  

    // Implementing pure virtual methods from Module  
    bool init(Engine* engine) override;
    void update(Engine& engine, float dt) override {}  
    void render(Engine& engine) override {}  
    void shutdown(Engine& engine) override {}  

private:  
    std::unordered_map<int, std::unique_ptr<GameObject>> gameObjects;
    std::vector<int> order;  
};
