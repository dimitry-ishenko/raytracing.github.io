#ifndef SOLID_HPP
#define SOLID_HPP

#include "color.hpp"
#include "point.hpp"
#include "texture.hpp"

struct solid : texture
{
    color3 color;

    explicit solid(color3 color) : color{std::move(color)} { }

    virtual color3 value(const point2&, const point3&) const { return color; }
};

#endif
