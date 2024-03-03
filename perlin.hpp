#ifndef PERLIN_HPP
#define PERLIN_HPP

#include "point.hpp"
#include "random.hpp"

#include <array>
#include <cstdint>
#include <numeric>

struct perlin
{
    perlin()
    {
        for (auto& p : perm)
        {
            std::iota(p.begin(), p.end(), 0);
            for (auto i = p.size() - 1; i > 0; --i) std::swap(p[i], p[rnd() * i]);
        }
        for (auto& n : rand) n = rnd();
    }

    auto noise(const point3& p) const
    {
        std::uint8_t x = 4 * p.x(), y = 4 * p.y(), z = 4 * p.z();
        return rand[ perm[0][x] ^ perm[1][y] ^ perm[2][z] ];
    }

private:
    std::array<int, 256> perm[3];
    std::array<double, 256> rand;
};

#endif
