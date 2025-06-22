#pragma once
#include "Actor.h"

enum class EnemyType {
	None = 0,
	Slime = 1,
	Goblin = 2,
	Troll = 3,
	Dragon = 4
};

class Enemy : public Actor {
protected:
	EnemyType type;
	int weight;
	int minCount;
	int maxCount;

	Enemy()
		: Actor()/* etc */
	{
		// common enemy init…
	}

};
