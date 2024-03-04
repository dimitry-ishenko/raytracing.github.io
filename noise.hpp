#ifndef NOISE_HPP
#define NOISE_HPP

#include "color.hpp"
#include "perlin.hpp"
#include "texture.hpp"

struct noise : texture
{
    explicit noise(double scale = 1) : scale{scale} { }

    virtual color3 value(const point2&, const point3& p) const override
    {
        return color3{1, 1, 1} * gen.turb(scale * p, 7);
    }

private:
    perlin gen;
    double scale;
};

#endif
