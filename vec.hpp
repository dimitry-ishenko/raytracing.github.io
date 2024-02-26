#ifndef VEC_HPP
#define VEC_HPP

#include "array.hpp"

struct vec3 : array<double, 3>
{
    constexpr auto x() const { return (*this)[0]; }
    constexpr auto y() const { return (*this)[1]; }
    constexpr auto z() const { return (*this)[2]; }
};

#endif
