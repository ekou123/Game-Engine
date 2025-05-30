#pragma once
#include <iostream>
#include <utility> // for std::pair
#include <functional> // for std::hash
#include <unordered_map>  
#include <vector>
#include <memory>
#include "Module.h"
#include "GameObject.h"

struct PairHash
{
    size_t operator()(std::pair<int, int> const& pair) const noexcept
    {
        return std::hash<long long>()(
            (static_cast<long long>(pair.first) << 32) | static_cast<unsigned long long>(pair.second)
            );
    }
};

class Engine;
class Block;
class PositionComponent;

class BlockRegistryModule : public Module {  
public:  
    static BlockRegistryModule& getInstance() {  
        static BlockRegistryModule instance;  
        return instance;  
    };  

    void registerBlock(int id, std::unique_ptr<GameObject> gameObject);

    void addBlock(std::unique_ptr<GameObject> gameObject);

    const std::unique_ptr<GameObject>& getAt(int tileX, int tileY) const
    {
        auto key = std::make_pair(tileX, tileY);
		auto it = worldObjects.find(key);

        if (it == worldObjects.end())
        {
           std::cerr << "GameObject at position (" << tileX << ", " << tileY
                << ") not found.\n";
		   return nullptr;
		}
		return it->second;
	    //return worldObjects.find(id);
    }

    const auto& getAll() { return worldObjects; }

    const std::vector<int>& allIDs() const { return order; }  

    // Implementing pure virtual methods from Module  
    bool init(Engine* engine) override;
    void update(Engine& engine, float dt) override;
    void render(Engine& engine) override;

    void shutdown(Engine& engine) override;

private:
    int nextID = 0;;
    std::unordered_map<int, std::unique_ptr<GameObject>> gameObjects;
    std::unordered_map<std::pair<int, int>, std::unique_ptr<GameObject>, PairHash> worldObjects;
    std::vector<int> order;
    std::vector<int> worldOrder;
};
