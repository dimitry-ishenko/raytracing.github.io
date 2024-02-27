#ifndef HIT_HPP
#define HIT_HPP

#include "material.hpp"
#include "point.hpp"
#include "vec.hpp"

#include <optional>

struct hit
{
    point3 point;
    vec3 norm; // unit vec
    double t;

    bool front;
    shared_material mat;
};

using optional_hit = std::optional<hit>;

#endif
