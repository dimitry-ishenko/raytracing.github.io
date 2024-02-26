#ifndef AABB_HPP
#define AABB_HPP

#include "interval.hpp"
#include "point.hpp"

#include <algorithm>

struct aabb
{
    interval ix, iy, iz;

    static aabb from(const point3& a, const point3& b)
    {
        return aabb{
            padded(a.x(), b.x()),
            padded(a.y(), b.y()),
            padded(a.z(), b.z()),
        };
    }

private:
    static interval padded(double m, double n)
    {
        auto [min, max] = std::minmax(m, n);
        return padded_if_less(interval{min, max}, .0001);
    }
};

auto merge(const aabb& box0, const aabb& box1)
{
    return aabb{
        merge(box0.ix, box1.ix),
        merge(box0.iy, box1.iy),
        merge(box0.iz, box1.iz),
    };
}

#endif
