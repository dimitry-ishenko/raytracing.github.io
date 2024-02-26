#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <algorithm>
#include <limits>

constexpr const auto inf = std::numeric_limits<double>::infinity();

struct interval
{
    double min, max;
};

constexpr auto len(const interval& in) { return in.max - in.min; }

constexpr auto merge(const interval& ix, const interval& iy)
{
    return interval{ std::min(ix.min, iy.min), std::max(ix.max, iy.max) };
}

constexpr auto pad(const interval& in, double p)
{
    return interval{ in.min - p / 2, in.max + p / 2 };
}

constexpr auto surr(const interval& in, double t) { return in.min < t && t < in.max; }

#endif
