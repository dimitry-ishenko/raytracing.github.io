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
        static rnd_sphere3_gen rnd{1};

        auto dir = reflect(unit{ray.dir}, hit.norm) + fuzz * rnd();
        if (dot(dir, hit.norm) < 0) return { };

        return scatter{ ray3{hit.point, dir}, albedo };
    }

private:
    static vec3 reflect(const unit<vec3>& l, const unit<vec3>& n)
    {
        // https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
        auto cos_th1 = dot(-n, l);
        return l + 2 * cos_th1 * n;
    }
};

#endif
