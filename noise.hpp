#ifndef NOISE_HPP
#define NOISE_HPP

#include "color.hpp"
#include "perlin.hpp"
#include "texture.hpp"

#include <cmath>

struct noise : texture
{
    explicit noise(double scale = 1) : scale{scale} { }

    virtual color3 value(const point2&, const point3& p) const override
    {
        auto s = scale * p;
        return color3{.5, .5, .5} * (1 + std::sin(s.z() + 10 * gen.turb(s, 7)));
    }

private:
    perlin gen;
    double scale;
};

#endif
