#ifndef QUAD_HPP
#define QUAD_HPP

#include "aabb.hpp"
#include "material.hpp"
#include "object.hpp"
#include "point.hpp"
#include "vec.hpp"

#include <cmath>
#include <memory>

struct quad : object
{
    quad(const point3& q, const vec3& u, const vec3& v, std::shared_ptr<material> mat) :
        q{q}, u{u}, v{v}, mat{std::move(mat)}
    {
        auto n = cross(u, v);
        norm = unit(n);
        d = dot(norm, q);
        w = n / dot(n, n);

        auto box0 = aabb{q, q + u + v};
        auto box1 = aabb{q + u, q + v};
        bbox = merge(box0, box1);
    }

    virtual std::optional<hit> get_hit(const ray3& ray, interval ti) const override
    {
        auto den = dot(norm, ray.dir);
        if (std::abs(den) < 1e-8) return { };

        auto t = (d - dot(norm, ray.origin)) / den;
        if (!surr(ti, t)) return { };

        auto point = ray.at(t);

        auto p = point - q;
        auto a = dot(w, cross(p, v));
        auto b = dot(w, cross(u, p));
        if (!surr(interval{0, 1}, a) || !surr(interval{0, 1}, b)) return { };

        auto front = dot(ray.dir, norm) < 0;

        return hit{ point, front ? norm : -norm, t, front, mat, point2{a, b} };
    }

private:
    point3 q;
    vec3 u, v;
    std::shared_ptr<material> mat;

    vec3 norm; // unit vec
    double d;
    vec3 w;
};

#endif
