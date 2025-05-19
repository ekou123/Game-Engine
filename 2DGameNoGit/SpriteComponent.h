#pragma once
#include "Actor.h"
#include "Camera.h"
#include "Component.h"
#include "PositionComponent.h"
#include "SDL3/SDL.h"

struct SpriteComponent : public Component
{
	SDL_Texture* texture;
	SDL_Rect srcRect;

	SpriteComponent(SDL_Texture* tex, SDL_Rect src)
		: texture(tex), srcRect(src)
	{}

	void init() override {}

	void update(float) override
	{}

	void render(SDL_Renderer* r, const Camera& cam) {
		PositionComponent* pos = owner->getComponent<PositionComponent>();
		int x = pos->x;
		int y = pos->y;

		SDL_FRect dst{ x - cam.x, y - cam.y, float(srcRect.w), float(srcRect.h) };
		SDL_RenderTexture(r, tex, &srcRect, &dst);
	}
};