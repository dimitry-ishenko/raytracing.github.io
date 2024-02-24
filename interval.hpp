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
    auto min = std::min(ix.min, iy.min), max = std::max(ix.max, iy.max);
    return interval{min, max};
}

constexpr auto pad(const interval& in, double p)
{
    auto min = in.min - p / 2, max = in.max + p / 2;
    return interval{min, max};
}

constexpr auto surr(const interval& in, double t) { return in.min < t && t < in.max; }

#endif
