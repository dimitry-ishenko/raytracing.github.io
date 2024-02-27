#ifndef LAMBERT_HPP
#define LAMBERT_HPP

#include "color.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "random.hpp"
#include "ray.hpp"

struct lambert : material
{
    color3 albedo;

    explicit lambert(const color3& albedo) : albedo{albedo} { }

    virtual optional_scatter get_scatter(const ray3& ray, const hit& hit) const override
    {
        auto dir = hit.norm + unit(rnd_sphere3());
        if (near_0(dir)) dir = hit.norm;

        return scatter{ ray3{hit.point, dir, ray.time}, albedo };
    }
};

#endif
