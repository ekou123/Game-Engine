#pragma once
#include "ChunkCoord.h"
#include "Constants.h"
#include "GameObject.h"

struct Chunk
{
	ChunkCoord coord;
	std::vector<GameObject*> blocks;
};
