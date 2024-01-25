#ifndef RAY_HPP
#define RAY_HPP

#include "point.hpp"
#include "vec.hpp"

struct ray3
{
    point3 origin;
    vec3 dir;

    constexpr auto at(double x) const { return origin + x * dir; }
};

#endif
