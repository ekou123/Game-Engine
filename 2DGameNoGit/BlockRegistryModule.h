#pragma once  
#include "BlockType.h"  
#include "Module.h"  
#include <unordered_map>  
#include <vector>

class BlockRegistryModule : public Module {  
public:  
    static BlockRegistryModule& getInstance() {  
        static BlockRegistryModule instance;  
        return instance;  
    };  

    void registerBlock(const BlockType& block) {  
        blockTypes[block.id] = block;  
        order.push_back(block.id);

    }  

    const BlockType& get(int id) const { return blockTypes.at(id); }  

    const std::vector<int>& allIDs() const { return order; }  

    // Implementing pure virtual methods from Module  
    bool init(Engine* engine) override;
    void update(Engine& engine, float dt) override {}  
    void render(Engine& engine) override {}  
    void shutdown(Engine& engine) override {}  

private:  
    std::unordered_map<int, BlockType> blockTypes;  
    std::vector<int> order;  
};