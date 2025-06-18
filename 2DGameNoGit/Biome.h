#pragma once
#include <random>
#include <vector>

#include "Chunk.h"
#include "FastNoiseLite.h"

class Biome
{
public:
	FastNoiseLite noise;
	int maxTerrainHeight;

	virtual ~Biome() = default;

	// Called once when the chunk is first generated:
	virtual void generateTerrain(Chunk& chunk, Engine* engine) const = 0;

	// Pick a random set of enemies to spawn in this chunk:
	//virtual std::vector<EnemyType> spawnEnemies(std::mt19937& rng) const = 0;

	const float fBm(int x) const
	{
		float total = 0, freq = 1, amp = 1, maxA = 0;
		for (int o = 0; o < 4; ++o)
		{
			total += noise.GetNoise(x * freq, 0.f) * amp;
			maxA += amp;
			amp *= 0.5f; // Decrease amplitude
			freq *= 2.0f; // Increase frequency
		}
		return total / maxA;
	}

private:
	
	
};
