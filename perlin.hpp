#ifndef PERLIN_HPP
#define PERLIN_HPP

#include "point.hpp"
#include "random.hpp"

#include <iterator>
#include <numeric>

struct perlin
{
    perlin()
    {
        for (auto& p : perm)
        {
            std::iota(std::begin(p), std::end(p), 0);
            for (auto i = std::size(p) - 1; i > 0; --i) std::swap(p[i], p[ std::size_t(rnd() * i) ]);
        }
        for (auto& n : rand) n = rnd();
    }

    auto noise(const point3& p) const
    {
        int x = std::floor(p.x());
        int y = std::floor(p.y());
        int z = std::floor(p.z());

        auto u = p.x() - x, v = p.y() - y, w = p.z() - z;
        u = u * u * (3 - 2 * u);
        v = v * v * (3 - 2 * v);
        w = w * w * (3 - 2 * w);

        double acc = 0;
        for (auto i = 0; i < 2; ++i)
            for (auto j = 0; j < 2; ++j)
                for (auto k = 0; k < 2; ++k)
                    acc += (i*u + (1-i) * (1-u)) * (j*v + (1-j) * (1-v)) * (k*w + (1-k) * (1-w)) *
                        rand[ perm[0][(x+i) & 255] ^ perm[1][(y+j) & 255] ^ perm[2][(z+k) & 255] ];

        return acc;
    }

private:
    int perm[3][256];
    double rand[256];
};

#endif
