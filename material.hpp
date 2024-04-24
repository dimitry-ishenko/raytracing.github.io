#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "ray.hpp"

#include <optional>

struct hit;

struct scatter
{
    ray3 ray;
    color3 atten;
    double pdf;
};

struct material
{
    virtual std::optional<scatter> get_scatter(const ray3&, const hit&) const { return { }; }
    virtual std::optional<color3>  get_emitted(const point2&, const point3&) const { return { }; }
};

#endif
