#pragma once

struct ChunkCoord {
    int x, y;
    bool operator==(ChunkCoord o) const { return x == o.x && y == o.y; }
};
struct ChunkHash {
    size_t operator()(ChunkCoord const& c) const noexcept {
        return std::hash<long long>()(((long long)c.x << 32) | (unsigned long long)c.y);
    }
};
