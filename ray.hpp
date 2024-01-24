#ifndef RAY_HPP
#define RAY_HPP

#include "point.hpp"

class ray
{
    point3 orig_;
    dir3 dir_;

public:
    ray(point3 orig, dir3 dir) : orig_{std::move(orig)}, dir_{std::move(dir)} { }

    constexpr const auto& orig() const { return orig_; }
    constexpr const auto& dir() const { return dir_; }

    constexpr auto at(double t) { return orig_ + t * dir_; }
};

#endif
