#pragma once
#include "Engine.h"
#include "Block.h"

class DirtBlock : public Block
{
public:
	DirtBlock(Engine* engine, int worldX, int worldY, int blockID);
};