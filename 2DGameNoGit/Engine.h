#pragma once
#include <vector>
#include <memory>
#include <SDL3/SDL.h>


class Block;
class GameObject; // Forward declaration
class Player;
struct Module;
class Engine;

// Guild name: Benison. Means a blessing. So you could call someone a Benison of Light or something like that.
 
class Engine {
public:
	Engine() = default;
	~Engine() = default;

	// non-copyable
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	// move allowed if you really need it
	Engine(Engine&&) = default;
	Engine& operator=(Engine&&) = default;

	//Engine() : window(nullptr), renderer(nullptr), running(false) {}
	bool init(const char* title, int w, int h);
	void registerModule(std::unique_ptr<Module> module);
	void registerPlayer(Player* player) { currentPlayer = player; }
	void run();
	void shutdown();
	void addGameObject(GameObject* gameObject);
	void removeGameObject(GameObject* gameObject);
	void addBlock(Block* block);

	SDL_Window* window;
	SDL_Renderer* renderer;

private:
	std::vector<std::unique_ptr<Module>> modules;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	Player* currentPlayer = nullptr;
	bool running;
	float deltaTime;
	SDL_Event event;

	//void handleEvents();
	//void updateModules();
	//void renderModules();
	//void shutdownModules();
};