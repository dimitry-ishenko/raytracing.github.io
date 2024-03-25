#ifndef AABB_HPP
#define AABB_HPP

#include "array.hpp"
#include "interval.hpp"
#include "point.hpp"
#include "ray.hpp"

#include <algorithm>

struct aabb : array<interval, 3>
{
    aabb() = default;
    
    aabb(interval x, interval y, interval z) :
        array{ padded(x), padded(y), padded(z) }
    { }

    aabb(const point3& a, const point3& b) :
        array{ padded_interval(a.x(), b.x()), padded_interval(a.y(), b.y()), padded_interval(a.z(), b.z()) }
    { }

    void merge(const aabb& box)
    {
        data()[0].merge(box[0]);
        data()[1].merge(box[1]);
        data()[2].merge(box[2]);
    }

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

private:
    interval padded_interval(double m, double n)
    {
        auto [min, max] = std::minmax(m, n);
        return padded(interval{min, max});
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
