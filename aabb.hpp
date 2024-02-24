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
            to_interval(a.x(), b.x()),
            to_interval(a.y(), b.y()),
            to_interval(a.z(), b.z()),
        };
    }

private:
    static interval to_interval(double m, double n)
    {
        auto [min, max] = std::minmax(m, n);

        interval in{min, max};
        return len(in) < .0001 ? pad(in, .0001) : in;
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
