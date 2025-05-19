#pragma once
#include "BlockRegistryModule.h"
#include "GameObject.h"
#include "SpriteComponent.h"

class Block : public GameObject {
public:
	Block(Engine* engine, int worldX, int worldU, int blockID)
	{
		init(engine, worldX, worldY);

		auto& type = BlockRegistryModule::getInstance().get(blockID);
		addComponent<SpriteComponent>(engine->renderer, type.srcRect);
	}

	void render(SDL_Renderer* ren, const Camera& cam)
	{
		auto pos = getComponent<PositionComponent>();
		auto sprite = getComponent<SpriteComponent>();
		if (pos && sprite)
		{
			sprite->render(ren, cam);
		}
	}
};
