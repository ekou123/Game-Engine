#include "Block.h"
#include "Engine.h"
#include "BlockRegistryModule.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include <iostream>
#include <SDL3/SDL.h>

Block::Block(Engine* engine, int worldX, int worldY, int blockID)
{
	init(engine, worldX, worldY, blockID);

	//auto& type = BlockRegistryModule::getInstance().get(blockID);
	//addComponent<SpriteComponent>(engine->renderer, type->srcRect);
}

void Block::render(SDL_Renderer* ren, const Camera& cam)
{
	//std::cerr << "Rendering Block Object" << std::endl;
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
		sprite->render(ren, cam);
	}


}