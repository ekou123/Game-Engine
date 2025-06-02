#include "DirtBlock.h"

#include "SpriteComponent.h"

DirtBlock::DirtBlock(Engine* engine, int worldX, int worldY, int blockID)
	: Block(engine, worldX, worldY, blockID)
{
	name = "DirtBlock";
	setIsSolid(true); // Dirt blocks are solid

	init(engine, worldX, worldY, blockID);

	SDL_FRect srcRect{ 0.0f, 0.0f, 32.0f, 32.0f }; // Assuming the blockID corresponds to a texture in the registry

	//auto& type = BlockRegistryModule::getInstance().get(blockID);
	addComponent<SpriteComponent>(engine->renderer, srcRect, "dirt_block.bmp");
}
