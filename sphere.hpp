#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "ray.hpp"
#include "types.hpp"

#include <optional>

struct sphere
{
    point3 center;
    double radius;

    std::optional< unit<vec3> > hit_norm(const ray3& ray) const
    {
        auto rel = ray.origin - center;

        auto a = dot(ray.dir, ray.dir);
        auto b = 2 * dot(ray.dir, rel);
        auto c = dot(rel, rel) - radius * radius;

        if (auto d = b * b - 4 * a * c; d >= 0)
        {
            auto t = (-b - std::sqrt(d)) / (2 * a);
            return unit(ray.at(t) - center);
        }
        else return { };
    }
};

#endif
