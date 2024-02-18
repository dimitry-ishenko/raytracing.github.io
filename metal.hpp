#ifndef METAL_HPP
#define METAL_HPP

#include "color.hpp"
#include "material.hpp"
#include "object.hpp" // hit
#include "random.hpp"
#include "vec.hpp"

struct metal : material
{
    color3 albedo;
    double fuzz;

    metal(const color3& albedo, double fuzz) : albedo{albedo}, fuzz{fuzz} { }

    virtual std::optional<scatter> get_scatter(const ray3& ray, const hit& hit) const override
    {
        // https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
        auto l = ray.dir;
        auto n = unit{hit.norm};

        auto cos_th1 = dot(-n, l);
        auto ref = l + 2 * cos_th1 * n;

        ref += fuzz * unit{rnd_sphere3()};
        if (dot(ref, hit.norm) < 0) return { };

        return scatter{ ray3{hit.point, ref}, albedo };
    }
};

#endif
