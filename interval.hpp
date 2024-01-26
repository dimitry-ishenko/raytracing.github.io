#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <limits>

constexpr const auto inf = std::numeric_limits<double>::infinity();

struct interval
{
    double min, max;

    constexpr auto surr(double t) const { return min <  t && t <  max; }
};

#endif
