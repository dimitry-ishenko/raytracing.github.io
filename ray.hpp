#ifndef RAY_HPP
#define RAY_HPP

#include "types.hpp"
#include "vec.hpp"

class ray3
{
    point3 orig_;
    vec3 dir_;

public:
    ray3(point3 orig, vec3 dir) : orig_{std::move(orig)}, dir_{std::move(dir)} { }

    constexpr const auto& orig() const { return orig_; }
    constexpr const auto& dir() const { return dir_; }

    constexpr auto at(double t) { return orig_ + t * dir_; }
};

#endif
