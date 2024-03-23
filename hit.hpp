#ifndef HIT_HPP
#define HIT_HPP

#include "material.hpp"
#include "point.hpp"
#include "vec.hpp"

#include <memory>

struct hit
{
    point3 point;
    vec3 norm; // unit vec
    double t;

    bool front;
    std::shared_ptr<material> mat;
    point2 uv;
};

#endif
