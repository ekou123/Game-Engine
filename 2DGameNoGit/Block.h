#pragma once

#include "Camera.h"      // for Camera
#include "GameObject.h" // for GameObject
#include <iostream>    // for std::cout, std::endl





class Engine;

class Block : public GameObject {
public:
	Block(Engine* engine, int worldX, int worldY, int blockID);
	

	void render(SDL_Renderer* ren, const Camera& cam);



private:
	std::string name = "";


};
