#ifndef LAMBERT_HPP
#define LAMBERT_HPP

#include "color.hpp"
#include "material.hpp"
#include "object.hpp" // hit
#include "random.hpp"

struct lambert : material
{
    color3 albedo;

    explicit lambert(const color3& albedo) : albedo{albedo} { }

    virtual std::optional<scatter> get_scatter(const ray3&, const hit& hit) const override
    {
        static rnd_sphere3_gen rnd{1};

        auto dir = hit.norm + rnd();
        if (near_0(dir)) dir = hit.norm;

        return scatter{ ray3{hit.point, dir}, albedo };
    }
};

#endif
