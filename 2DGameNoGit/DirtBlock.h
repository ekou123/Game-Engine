#pragma once
#include "Block.h"


class DirtBlock : public Block
{
public:
	DirtBlock(Engine* engine, int worldX, int worldY)
		: Block(engine, worldX, worldY)
	{
		name = "Dirt Block";
	}
};
