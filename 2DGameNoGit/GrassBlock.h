#pragma once
#include "Engine.h"
#include "Block.h"           // ← this must pull in the *definition* of Block
#include "BlockRegistryModule.h"
#include "SpriteComponent.h"

class DirtBlock : public Block
{
	DirtBlock(Engine* engine, int worldX, int worldY, int blockID)
		: Block(engine, worldX, worldY, blockID)
	{
		init(engine, worldX, worldY, blockID);

		//auto& type = BlockRegistryModule::getInstance().get(blockID);
		//addComponent<SpriteComponent>(engine->renderer, type->srcRect);
	}

};
