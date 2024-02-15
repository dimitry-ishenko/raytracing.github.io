#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "point.hpp"
#include "ray.hpp"
#include "vec.hpp"

#include <memory>
#include <optional>
#include <vector>

struct hit
{
    point3 point;
    unit<vec3> norm;
    double t;
    bool front;
};

struct object
{
    virtual std::optional<hit> get_hit(const ray3&, double t_min, double t_max) const = 0;
};

struct object_list : object
{
    std::vector<std::unique_ptr<object>> children;

    virtual std::optional<hit> get_hit(const ray3& ray, double t_min, double t_max) const override
    {
        std::optional<hit> my_hit;

        for (const auto& child : children)
            if (auto hit = child->get_hit(ray, t_min, t_max))
            {
                t_max = hit->t;
                my_hit = hit;
            }

        return my_hit;
    }

};

#endif
