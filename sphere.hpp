#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "ray.hpp"
#include "types.hpp"

struct sphere
{
    point3 center;
    double radius;

    bool is_hit(const ray3& ray) const
    {
        auto oc = ray.origin - center;

        auto a = dot(ray.dir, ray.dir);
        auto b = 2 * dot(ray.dir, oc);
        auto c = dot(oc, oc) - radius * radius;

        auto d = b * b - 4 * a * c;
        return d >= 0;
    }
};

#endif
