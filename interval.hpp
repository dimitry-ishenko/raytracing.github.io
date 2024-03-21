#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <algorithm>
#include <limits>

constexpr const auto inf = std::numeric_limits<double>::infinity();

struct interval
{
    double min = +inf, max = -inf;
};

constexpr auto len(const interval& in) { return in.max - in.min; }

constexpr auto merge(const interval& ix, const interval& iy)
{
    return interval{ std::min(ix.min, iy.min), std::max(ix.max, iy.max) };
}

constexpr auto padded(interval in)
{
    constexpr auto p = .0001;
    if (len(in) < p) in.min -= p / 2, in.max += p / 2;
    return in;
}

constexpr auto padded_if_less(interval in, double p)
{
    if (len(in) < p) { in.min -= p / 2; in.max += p / 2; }
    return in;
}

constexpr auto surr(const interval& in, double t) { return in.min < t && t < in.max; }

#endif
