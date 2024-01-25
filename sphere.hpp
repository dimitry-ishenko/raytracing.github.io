#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "point.hpp"
#include "ray.hpp"

#include <optional>

struct sphere
{
    point3 center;
    double radius;

    std::optional< unit<vec3> > hit_norm(const ray3& ray) const
    {
        auto rel = ray.origin - center;

        auto a = len_2(ray.dir);
        auto h = dot(ray.dir, rel);
        auto c = len_2(rel) - radius * radius;

        if (auto d = h * h - a * c; d >= 0)
        {
            auto t = (-h - std::sqrt(d)) / a;
            return unit(ray.at(t) - center);
        }
        else return { };
    }
};

#endif
