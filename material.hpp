#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "ray.hpp"

#include <memory>
#include <optional>

struct hit;

struct scatter
{
    ray3 ray;
    color3 atten;
};

struct material
{
    virtual std::optional<scatter> get_scatter(const ray3& ray, const hit&) const = 0;
};

using shared_material = std::shared_ptr<material>;

#endif
