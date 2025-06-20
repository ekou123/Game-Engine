

#include "StoneBlock.h"

#include "SpriteComponent.h"

StoneBlock::StoneBlock(Engine* engine, int worldX, int worldY, int blockID)
	: Block(engine, worldX, worldY, blockID)
{
	name = "DirtBlock";
	setIsSolid(false); // Dirt blocks are solid

	init(engine, worldX, worldY, blockID);

	SDL_FRect srcRect{ 0.0f, 0.0f, 32.0f, 32.0f }; // Assuming the blockID corresponds to a texture in the registry

	//auto& type = BlockRegistryModule::getInstance().get(blockID);
	addComponent<SpriteComponent>(engine->renderer, srcRect, "stone_block.bmp");
}
