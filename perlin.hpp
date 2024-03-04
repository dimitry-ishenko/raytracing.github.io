#ifndef PERLIN_HPP
#define PERLIN_HPP

#include "point.hpp"
#include "random.hpp"
#include "vec.hpp"

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
        for (auto& n : rand) n = unit(rnd_vec3());
    }

    auto noise(const point3& p) const
    {
        int x = std::floor(p.x());
        int y = std::floor(p.y());
        int z = std::floor(p.z());

        auto u = p.x() - x; auto uu = u * u * (3 - 2 * u);
        auto v = p.y() - y; auto vv = v * v * (3 - 2 * v);
        auto w = p.z() - z; auto ww = w * w * (3 - 2 * w);

        auto acc = 0.;
        for (auto i = 0; i < 2; ++i)
            for (auto j = 0; j < 2; ++j)
                for (auto k = 0; k < 2; ++k)
                {
                    vec3 weight{u - i, v - j, w - k};
                    auto c = rand[ perm[0][(x+i) & 255] ^ perm[1][(y+j) & 255] ^ perm[2][(z+k) & 255] ];

                    acc += (i*uu + (1-i)*(1-uu)) * (j*vv + (1-j)*(1-vv)) * (k*ww + (1-k)*(1-ww)) * dot(c, weight);
                }

        return acc;
    }

private:
    int perm[3][256];
    vec3 rand[256];
};

#endif
