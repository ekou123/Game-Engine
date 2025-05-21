#pragma once
#include "BlockRegistryModule.h"
#include "GameObject.h"
#include "SpriteComponent.h"

class Block : public GameObject {
public:
	Block(Engine* engine, int worldX, int worldY, int blockID)
	{
		init(engine, worldX, worldY);

		auto& type = BlockRegistryModule::getInstance().get(blockID);
		//addComponent<SpriteComponent>(engine->renderer, type->srcRect);
	}

	void render(SDL_Renderer* ren, const Camera& cam)
	{
		auto pos = getComponent<PositionComponent>();
		if (!pos)
		{
			std::cerr << "PositionComponent not found on Block Object" << std::endl;
			return;
		}
		auto sprite = getComponent<SpriteComponent>();
		if (!sprite)
		{
			std::cerr << "SpriteComponent not found on Block Object" << std::endl;
			return;
		}

		if (pos && sprite)
		{
			//sprite->render(ren, cam);
		}

		
	}

private:
	std::string name = "";


};
