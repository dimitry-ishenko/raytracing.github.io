#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "aabb.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "object.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vec.hpp"

#include <cmath>
#include <numbers>

using std::numbers::pi;

struct sphere3 : object
{
    point3 center;
    double radius;
    shared_material mat;
    vec3 vel;

    sphere3(const point3& center, double radius, shared_material mat) :
        sphere3{ center, center, radius, std::move(mat) }
    { }

    sphere3(const point3& center0, const point3& center1, double radius, shared_material mat) :
        center{center0}, radius{radius}, mat{std::move(mat)}, vel{center1 - center0}
    {
        auto rvec = vec3{radius, radius, radius};
        auto box0 = aabb::from(center0 - rvec, center0 + rvec);
        auto box1 = aabb::from(center1 - rvec, center1 + rvec);
        bbox = merge(box0, box1);
    }

    virtual optional_hit get_hit(const ray3& ray, interval ti) const override
    {
        auto center_t = center + vel * ray.time;
        auto rel = ray.origin - center_t;

        auto a = len_2(ray.dir);
        auto h = dot(ray.dir, rel);
        auto c = len_2(rel) - radius * radius;

        auto d = h * h - a * c;
        if (d < 0) return { };

        auto sqrt_d = std::sqrt(d);

        auto t = (-h - sqrt_d) / a;
        if (!surr(ti, t))
        {
            t = (-h + sqrt_d) / a;
            if (!surr(ti, t)) return { };
        }

        auto point = ray.at(t);
        auto norm  = (point - center_t) / radius;

        auto front = dot(ray.dir, norm) < 0;

        auto th = std::acos(-norm.y());
        auto ph = std::atan2(-norm.z(), norm.x()) + pi;
        point2 uv{ ph / (2 * pi), th / pi };

        return hit{ point, front ? norm : -norm, t, front, mat, uv };
    }
};

#endif
