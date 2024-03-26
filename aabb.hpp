#ifndef AABB_HPP
#define AABB_HPP

#include "interval.hpp"
#include "point.hpp"
#include "ray.hpp"

struct aabb
{
    interval x, y, z;

    constexpr aabb() = default;
    
    constexpr aabb(interval x, interval y, interval z) : x{padded(x)}, y{padded(y)}, z{padded(z)} { }

    constexpr aabb(const point3& a, const point3& b) :
        x{ padded(sorted(a.x(), b.x())) }, y{ padded(sorted(a.y(), b.y())) }, z{ padded(sorted(a.z(), b.z())) }
    { }

    void merge(const aabb& box)
    {
        x.merge(box.x);
        y.merge(box.y);
        z.merge(box.z);
    }

    constexpr auto&& ax(std::size_t n) const { const interval* d[] = {&x, &y, &z}; return *d[n]; }

    std::size_t longest_axis() const
    {
        return len(x) > len(y)
            ? (len(x) > len(z) ? 0 : 2)
            : (len(y) > len(z) ? 1 : 2);
    }

    bool is_hit(const ray3& ray, interval ti) const
    {
        for (std::size_t i = 0; i < 3; ++i)
        {
            auto [min, max] = std::minmax({
                (ax(i).min - ray.origin[i]) / ray.dir[i],
                (ax(i).max - ray.origin[i]) / ray.dir[i]
            });

            ti.min = std::max(ti.min, min);
            ti.max = std::min(ti.max, max);

            if (ti.max <= ti.min) return false;
        }
        return true;
    }
};

#endif
