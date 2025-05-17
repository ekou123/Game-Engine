#pragma once
// PerlinNoise.h — a very basic implementation

#include <cmath>
#include <array>
#include <numeric>
#include <random>

class PerlinNoise {
    std::array<int,512> perm;
public:
    PerlinNoise(unsigned seed = 2016) {
        // 1) fill 0…255
        for (int i = 0; i < 256; ++i)
            perm[i] = i;

        // 2) shuffle only the first half
        std::mt19937 gen(seed);
        std::shuffle(perm.begin(), perm.begin() + 256, gen);

        // 3) duplicate into the second half
        for (int i = 0; i < 256; ++i)
            perm[256 + i] = perm[i];
    }

    float noise(float x, float y) const {
        auto fade = [](float t) { return t * t * t * (t * (t * 6 - 15) + 10); };
        auto lerp = [](float a, float b, float t) { return a + t * (b - a); };
        auto grad = [](int hash, float x, float y) {
            int h = hash & 7;
            float u = h < 4 ? x : y;
            float v = h < 4 ? y : x;
            return (((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v));
            };

        int X = int(floor(x)) & 255;
        int Y = int(floor(y)) & 255;
        x -= floor(x);
        y -= floor(y);
        float u = fade(x), v = fade(y);
        int A = perm[X] + Y;
        int B = perm[X + 1] + Y;
        float res = lerp(
            lerp(grad(perm[A], x, y),
                grad(perm[B], x - 1, y), u),
            lerp(grad(perm[A + 1], x, y - 1),
                grad(perm[B + 1], x - 1, y - 1), u),
            v);
        return res;
    }
};