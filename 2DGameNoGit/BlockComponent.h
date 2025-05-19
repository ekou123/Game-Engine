#pragma once
#include "BlockRegistryModule.h"
#include "Component.h"

struct BlockComponent : public Component
{
	int blockID;
	bool isSolid;

	BlockComponent(int id)
		: blockID(id),
		isSolid(BlockRegistryModule::getInstance().get(id).isSolid)
	{}

	void init() override
	{}

	void update(float dt) override
	{}
};