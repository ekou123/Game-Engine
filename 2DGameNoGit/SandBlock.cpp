

#include "SandBlock.h"

#include "SpriteComponent.h"

SandBlock::SandBlock(Engine* engine, int worldX, int worldY, int blockID)
	: Block(engine, worldX, worldY, blockID)
{
	name = "SandBlock";
	setIsSolid(true); // Sand blocks are solid

	init(engine, worldX, worldY, blockID);

	SDL_FRect srcRect{ 0.0f, 0.0f, 32.0f, 32.0f }; // Assuming the blockID corresponds to a texture in the registry

	//auto& type = BlockRegistryModule::getInstance().get(blockID);
	addComponent<SpriteComponent>(engine->renderer, srcRect, "sand_block.bmp");
}
