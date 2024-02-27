#ifndef AABB_HPP
#define AABB_HPP

#include "array.hpp"
#include "interval.hpp"
#include "point.hpp"
#include "ray.hpp"

#include <algorithm>

struct aabb : array<interval, 3>
{
    auto longest_axis() const
    {
        return len(data()[0]) > len(data()[1])
            ? (len(data()[0]) > len(data()[2]) ? 0 : 2)
            : (len(data()[1]) > len(data()[2]) ? 1 : 2);
    }

    bool is_hit(const ray3& ray, interval ti) const
    {
        for (std::size_t i = 0; i < size(); ++i)
        {
            auto [min, max] = std::minmax({
                (data()[i].min - ray.origin[i]) / ray.dir[i],
                (data()[i].max - ray.origin[i]) / ray.dir[i]
            });

            ti.min = std::max(ti.min, min);
            ti.max = std::min(ti.max, max);

            if (ti.max <= ti.min) return false;
        }
        return true;
    }

    static aabb from(const point3& a, const point3& b)
    {
        auto padded = [](double m, double n)
        {
            auto [min, max] = std::minmax(m, n);
            return padded_if_less(interval{min, max}, .0001);
        };

        return aabb{
            padded(a.x(), b.x()),
            padded(a.y(), b.y()),
            padded(a.z(), b.z()),
        };
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
