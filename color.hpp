#ifndef COLOR_HPP
#define COLOR_HPP

#include "array.hpp"

struct color3 : array<double, 3>
{
    constexpr auto r() const { return data[0]; }
    constexpr auto g() const { return data[1]; }
    constexpr auto b() const { return data[2]; }
};

#endif
