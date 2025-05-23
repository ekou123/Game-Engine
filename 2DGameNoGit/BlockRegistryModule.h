#pragma once  
#include <iostream>

#include "BlockType.h"  
#include "Module.h"  
#include <unordered_map>  
#include <vector>

#include "DirtBlock.h"
#include "GameObject.h"

class BlockRegistryModule : public Module {  
public:  
    static BlockRegistryModule& getInstance() {  
        static BlockRegistryModule instance;  
        return instance;  
    };  

    void registerBlock(int id, std::unique_ptr<GameObject> gameObject) {
        std::cerr << " Registering Block.\n";
        

        if (gameObjects.count(id)) {
            std::cerr << "GameObject with ID " << id
                << " already exists. Overwriting.\n";
        }
        // move the unique_ptr into the map

        gameObjects.emplace(id, std::move(gameObject));
        order.push_back(id);
    }

    void addBlock(std::unique_ptr<GameObject> gameObject)
    {
        std::cerr << "Adding block to world\n";
    	int id = nextID++;

        if (worldObjects.count(id))
        {
			std::cerr << "GameObject with ID " << id << " already exists. Overwriting.\n";
        }

		worldObjects.emplace(id, std::move(gameObject));
		worldOrder.push_back(id);

    }

    const std::unique_ptr<GameObject> & get(int id) const { return worldObjects.at(id); }

	const std::unordered_map<int, std::unique_ptr<GameObject>>& getAll() { return worldObjects; }

    const std::vector<int>& allIDs() const { return order; }  

    // Implementing pure virtual methods from Module  
    bool init(Engine* engine) override
    {
        // Register blocks
        auto dirt = std::make_unique<DirtBlock>(engine, 0, 0, nextID);
        registerBlock(0, std::move(dirt));
        return true; // Initialization successful
    }
    void update(Engine& engine, float dt) override {}  
    void render(Engine& engine) override {}  
    void shutdown(Engine& engine) override {}  

private:
    int nextID = 0;;
    std::unordered_map<int, std::unique_ptr<GameObject>> gameObjects;
    std::unordered_map<int, std::unique_ptr<GameObject>> worldObjects;
    std::vector<int> order;
    std::vector<int> worldOrder;
};
