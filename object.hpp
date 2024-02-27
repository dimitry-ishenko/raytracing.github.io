#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "aabb.hpp"
#include "interval.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vec.hpp"

#include <memory>
#include <optional>
#include <vector>

struct material;

struct hit
{
    point3 point;
    vec3 norm; // unit vec
    double t;

    bool front;
    std::shared_ptr<material> mat;
};

struct object
{
    aabb bbox;

    virtual std::optional<hit> get_hit(const ray3&, interval) const = 0;
};

struct object_list : object
{
    virtual std::optional<hit> get_hit(const ray3& ray, interval ti) const override
    {
        std::optional<hit> my_hit;

        for (const auto& child : children)
            if (auto hit = child->get_hit(ray, ti))
            {
                ti.max = hit->t;
                my_hit = hit;
            }

        return my_hit;
    }

    std::vector<std::shared_ptr<object>> children;
};

#endif
