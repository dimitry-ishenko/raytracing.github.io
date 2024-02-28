#ifndef METAL_HPP
#define METAL_HPP

#include "color.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "random.hpp"
#include "ray.hpp"

struct metal : material
{
    color3 albedo;
    double fuzz;

    metal(color3 albedo, double fuzz) : albedo{std::move(albedo)}, fuzz{fuzz} { }

    virtual optional_scatter get_scatter(const ray3& ray, const hit& hit) const override
    {
        // https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
        auto l = ray.dir;
        auto n = hit.norm;

        auto cos_th1 = dot(-n, l);
        auto ref = l + 2 * cos_th1 * n;

        ref += fuzz * unit(rnd_sphere3());
        if (dot(ref, hit.norm) < 0) return { };

        return scatter{ ray3{hit.point, ref, ray.time}, albedo };
    }
};

#endif
