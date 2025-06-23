#pragma once
#include <random>
#include <vector>

#include "Chunk.h"
#include "Enemy.h"
#include "FastNoiseLite.h"

class Biome
{
public:
	FastNoiseLite noise;
	int maxTerrainHeight;
	std::vector<Enemy> enemies;
	std::unordered_map<std::unique_ptr<Enemy>, int> enemySpawns;

	virtual ~Biome() = default;

	// Called once when the chunk is first generated:
	virtual void generateTerrain(Chunk& chunk, Engine* engine) const = 0;

	// Pick a random set of enemies to spawn in this chunk:
	//virtual std::vector<EnemyType> spawnEnemies(std::mt19937& rng) const = 0;

	virtual std::vector<Enemy> spawnTable() const = 0;


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

	float getGroundHeight(int worldTileX) const
	{
		// raw noise in [-1..+1]
		float raw = noise.GetNoise(float(worldTileX) * 0.2f, 0.0f);

		// normalize to [0..1]
		float n = (raw + 1.0f) * 0.5f;

		// optional bias: e.g. flatten plains, sharpen peaks
		n = powf(n, 1.2f);

		// scale into [minH..maxH] in *tiles*
		constexpr float minH = 2.0f;                             // at least 2 tiles high
		float maxH = float(maxTerrainHeight);
		return n * (maxH - minH) + minH;
	}

private:
	
	
};
