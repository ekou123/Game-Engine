#include "DirtBlock.h"

DirtBlock::DirtBlock(Engine* engine, int worldX, int worldY, int blockID)
	: Block(engine, worldX, worldY, blockID)
{
	init(engine, worldX, worldY, blockID);

	//auto& type = BlockRegistryModule::getInstance().get(blockID);
	//addComponent<SpriteComponent>(engine->renderer, type->srcRect);
}