#ifndef LAMBERT_HPP
#define LAMBERT_HPP

#include "color.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "solid.hpp"
#include "texture.hpp"

struct lambert : material
{
    shared_texture albedo;

    explicit lambert(color3 albedo) : albedo{std::make_shared<solid>(std::move(albedo))} { }
    explicit lambert(shared_texture albedo) : albedo{std::move(albedo)} { }

    virtual optional_scatter get_scatter(const ray3& ray, const hit& hit) const override
    {
        auto dir = hit.norm + unit(rnd_sphere3());
        if (near_0(dir)) dir = hit.norm;

        return scatter{ ray3{hit.point, dir, ray.time}, albedo->value(hit.uv, hit.point) };
    }
};

#endif
