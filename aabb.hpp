#ifndef AABB_HPP
#define AABB_HPP

#include "array.hpp"
#include "interval.hpp"
#include "point.hpp"

#include <algorithm>

struct aabb : array<interval, 3>
{
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
        merge(box0[0], box1[0]),
        merge(box0[1], box1[1]),
        merge(box0[2], box1[2]),
    };
}

#endif
