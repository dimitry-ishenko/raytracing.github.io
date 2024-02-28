#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "color.hpp"
#include "point.hpp"

#include <memory>

struct texture
{
    virtual color3 value(const point2&, const point3&) const = 0;
};

using shared_texture = std::shared_ptr<texture>;

#endif
