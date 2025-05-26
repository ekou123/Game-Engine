#pragma once
#include "Actor.h"
#include "Camera.h"
#include "Component.h"
#include "PositionComponent.h"
#include "SDL3/SDL.h"

struct SpriteComponent : public Component
{
	SDL_Texture* texture;
	SDL_FRect srcRect;

	SpriteComponent(SDL_Renderer* r,
		const SDL_FRect& src,
		const std::string& assetPath)
	{
		SDL_Surface* surf = SDL_LoadBMP(assetPath.c_str());
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_DestroySurface(surf);
		srcRect = src;
	}

	void init() override {}

	void update(float) override
	{}

	void render(SDL_Renderer* r, const Camera& cam) {
		PositionComponent* pos = owner->getComponent<PositionComponent>();
		int x = pos->x;
		int y = pos->y;

		SDL_FRect dst{ x - cam.x, y - cam.y, float(srcRect.w), float(srcRect.h) };
		if (texture == nullptr) {
			SDL_Log("Texture is null, cannot render sprite.");
			return;
		}
		SDL_RenderTexture(r, texture, &srcRect, &dst);
	}
};