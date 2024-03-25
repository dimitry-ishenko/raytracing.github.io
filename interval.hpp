#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <limits>

constexpr const auto inf = std::numeric_limits<double>::infinity();

struct interval
{
    double min = +inf, max = -inf;

    constexpr void merge(const interval& in)
    {
        if (in.min < min) min = in.min;
        if (in.max > max) max = in.max;
    }
};

constexpr auto len(const interval& in) { return in.max - in.min; }

constexpr auto padded(interval in)
{
    constexpr auto p = .0001;
    if (len(in) < p) in.min -= p / 2, in.max += p / 2;
    return in;
}

constexpr auto surr(const interval& in, double t) { return in.min < t && t < in.max; }

#endif
