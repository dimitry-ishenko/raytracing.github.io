#ifndef VEC_HPP
#define VEC_HPP

#include "array.hpp"

struct vec2 : array<double, 2>
{
    constexpr auto x() const { return data()[0]; }
    constexpr auto y() const { return data()[1]; }
};

struct vec3 : array<double, 3>
{
    constexpr auto x() const { return data()[0]; }
    constexpr auto y() const { return data()[1]; }
    constexpr auto z() const { return data()[2]; }
};

#endif
