#pragma once
#include "Block.h"
#include "Engine.h"

class StoneBlock : public Block
{
public:
	StoneBlock(Engine* engine, int worldX, int worldY, int blockID);

};
