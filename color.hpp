#ifndef COLOR_HPP
#define COLOR_HPP

#include "array.hpp"
#include "vec.hpp"

struct color3 : array<double, 3>
{
    constexpr auto r() const { return (*this)[0]; }
    constexpr auto g() const { return (*this)[1]; }
    constexpr auto b() const { return (*this)[2]; }

    static auto from_vec3(const vec3& v) { return color3{v.x(), v.y(), v.z()}; }
};

#endif
