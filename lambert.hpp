#ifndef LAMBERT_HPP
#define LAMBERT_HPP

#include "color.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "math.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "solid.hpp"
#include "texture.hpp"

#include <memory>

struct lambert : material
{
    explicit lambert(color3 albedo) : albedo{std::make_shared<solid>(std::move(albedo))} { }
    explicit lambert(std::shared_ptr<texture> albedo) : albedo{std::move(albedo)} { }

    virtual std::optional<scatter> get_scatter(const ray3& ray, const hit& hit) const override
    {
        auto dir = rnd_sphere3();
        if (dot(dir, hit.norm) < 0) dir = -dir;

        auto pdf = .5 / pi;

        return scatter{ ray3{hit.point, dir, ray.time}, albedo->value(hit.uv, hit.point), pdf };
    }

private:
    std::shared_ptr<texture> albedo;
};

#endif
