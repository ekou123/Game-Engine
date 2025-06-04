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
        // 1) Try to load the BMP into a surface:
        SDL_Surface* surf = SDL_LoadBMP(assetPath.c_str());
        if (!surf) {
            // If SDL_LoadBMP fails, surf is null. Print out the SDL error.
            SDL_Log("SDL_LoadBMP failed for \"%s\": %s",
                assetPath.c_str(), SDL_GetError());
            // We bail out – texture stays null.
            return;
        }

        // 2) Create a texture from that surface:
        texture = SDL_CreateTextureFromSurface(r, surf);
        if (!texture) {
            // If texture creation fails, log the error.
            SDL_Log("SDL_CreateTextureFromSurface failed: %s",
                SDL_GetError());
            // Free the surface and bail.
            SDL_DestroySurface(surf);
            return;
        }

        // 3) We succeeded—free the surface and store the srcRect:
        SDL_DestroySurface(surf);
        srcRect = src;
    }

	void init(Engine* engine) override {}

	void update(float) override
	{}

	void render(SDL_Renderer* r, const Camera& cam) {
		
		PositionComponent* pos = owner->getComponent<PositionComponent>();
        //std::cerr << "x: " << pos->x << "y: " << pos->y << std::endl;
		int x = pos->x;
		int y = pos->y;

		SDL_FRect dst{ x - cam.x, y - cam.y, float(srcRect.w), float(srcRect.h) };
		if (texture == nullptr) {
			SDL_Log("Texture is null, cannot render sprite.");
			return;
		}
		//std::cerr << "Rendering sprite at position: (" << dst.x << ", " << dst.y << ")" << std::endl;
		SDL_RenderTexture(r, texture, &srcRect, &dst);
	}
};