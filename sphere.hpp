#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "point.hpp"

struct sphere3 : object
{
    point3 center;
    double radius;

    sphere3(const point3& center, double radius) : center{center}, radius{radius} { }

    virtual std::optional<hit> get_hit(const ray3& ray, interval ti) const override
    {
        auto rel = ray.origin - center;

        auto a = len_2(ray.dir);
        auto h = dot(ray.dir, rel);
        auto c = len_2(rel) - radius * radius;

        auto d = h * h - a * c;
        if (d < 0) return { };

        auto sqrt_d = std::sqrt(d);

        auto t = (-h - sqrt_d) / a;
        if (!ti.surr(t))
        {
            t = (-h + sqrt_d) / a;
            if (!ti.surr(t)) return { };
        }

        auto point = ray.at(t);
        auto norm  = unit{(point - center) / radius, adopt_unit};
        auto front = dot(ray.dir, norm) < 0;

        return hit{ point, front ? norm : -norm, t, front };
    }
};

#endif
