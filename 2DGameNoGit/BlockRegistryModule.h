#pragma once  
#include <iostream>
#include <map>
#include "Module.h"  
#include <unordered_map>  
#include <vector>

#include "DirtBlock.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "RenderModule.h"

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

    void addBlock(std::unique_ptr<Block> gameObject)
    {
        std::cerr << "Adding block to world\n";

		Block* gameObjectPtr = gameObject.get();
		PositionComponent* posComp = gameObjectPtr->getComponent<PositionComponent>();
        if (posComp == nullptr)
        {
	        std::cerr << "GameObject with ID " << id << " has no PositionComponent. Cannot add to world.\n";
			return;
        }

        std::vector<std::vector<int>> id = 

		worldObjects.emplace(id, std::move(gameObject));
		worldOrder.push_back(id);
        //map[tileY][tileX];
    }

    const std::unique_ptr<GameObject> & get(int id) const
    {
        auto it = worldObjects.find(id);
        if (it != worldObjects.end()) {
            return it->second;
        }

        std::cerr << "GameObject with ID " << id << " not found.\n";
        return nullptr;
	    //return worldObjects.find(id);
    }

	const std::unordered_map<std::vector<std::vector<int>>, std::unique_ptr<GameObject>>& getAll() { return worldObjects; }

    const std::vector<int>& allIDs() const { return order; }  

    // Implementing pure virtual methods from Module  
    bool init(Engine* engine)
    {
        // Register blocks
        auto dirt = std::make_unique<DirtBlock>(engine, 0, 0, nextID);
        registerBlock(0, std::move(dirt));
        return true; // Initialization successful
    }
    void update(Engine& engine, float dt)
    {
	    
    }  
    void render(Engine& engine)
    {
    }

    void shutdown(Engine& engine) {}  

private:
    int nextID = 0;;
    std::unordered_map<int, std::unique_ptr<GameObject>> gameObjects;
    std::unordered_map<std::vector<std::vector<int>>, std::unique_ptr<GameObject>> worldObjects;
    std::vector<int> order;
    std::vector<int> worldOrder;
};
