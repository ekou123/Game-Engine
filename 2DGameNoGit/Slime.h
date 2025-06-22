#pragma once
#include "Enemy.h"
#include "Player.h"
#include "PositionComponent.h"

class Slime : public Enemy {

	Slime() : Enemy()
	{
		type = EnemyType::Slime;
		weight = 5;
		minCount = 2;
		maxCount = 5;
	}

	void render(Engine* engine)
	{
		PositionComponent* posComp = getComponent<PositionComponent>();

		SDL_FRect rect = { posComp->x, posComp->y, Player::WIDTH, Player::HEIGHT };
		SDL_SetRenderDrawColor(engine->renderer, 255, 0, 0, 255); // Red color
		SDL_RenderFillRect(engine->renderer, &rect);
	}
};
