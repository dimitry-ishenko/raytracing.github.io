#ifndef POINT_HPP
#define POINT_HPP

#include "vec.hpp"

struct point3 : vec3<double>
{
    constexpr auto x() const { return data[0]; }
    constexpr auto y() const { return data[1]; }
    constexpr auto z() const { return data[2]; }
};

using dir3 = point3;

#endif
