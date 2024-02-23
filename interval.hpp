#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <limits>

constexpr const auto inf = std::numeric_limits<double>::infinity();

struct interval
{
    double min, max;
};

constexpr auto surr(const interval& in, double t) { return in.min < t && t < in.max; }

#endif
