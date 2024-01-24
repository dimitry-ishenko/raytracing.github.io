#ifndef RAY_HPP
#define RAY_HPP

#include "types.hpp"
#include "vec.hpp"

struct ray3
{
    point3 origin;
    vec3 dir;

    constexpr auto at(double l) { return origin + l * dir; }
};

#endif
