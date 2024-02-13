#ifndef METAL_HPP
#define METAL_HPP

#include "color.hpp"
#include "material.hpp"
#include "object.hpp" // hit

struct metal : material
{
    color3 albedo;

    explicit metal(const color3& albedo) : albedo{albedo} { }

    virtual std::optional<scatter> get_scatter(const ray3& ray_in, const hit& hit) const override
    {
        auto dir = ray_in.dir - 2 * dot(ray_in.dir, hit.norm) * hit.norm; // reflect
        return scatter{ ray3{hit.point, dir}, albedo };
    }
};

#endif
