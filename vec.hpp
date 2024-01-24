#ifndef VEC_HPP
#define VEC_HPP

#include "array.hpp"

struct vec3 : array3<double>
{
    constexpr auto x() const { return data[0]; }
    constexpr auto y() const { return data[1]; }
    constexpr auto z() const { return data[2]; }
};

#endif
