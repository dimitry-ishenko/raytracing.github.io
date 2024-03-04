#ifndef SOLID_HPP
#define SOLID_HPP

#include "color.hpp"
#include "point.hpp"
#include "texture.hpp"

struct solid : texture
{
    explicit solid(color3 color) : color{std::move(color)} { }

    virtual color3 value(const point2&, const point3&) const override { return color; }

private:
    color3 color;
};

#endif
