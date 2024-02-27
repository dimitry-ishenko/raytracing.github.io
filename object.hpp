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
using shared_material = std::shared_ptr<material>;

struct hit
{
    point3 point;
    vec3 norm; // unit vec
    double t;

    bool front;
    shared_material mat;
};

using optional_hit = std::optional<hit>;

struct object
{
    aabb bbox;

    virtual optional_hit get_hit(const ray3&, interval) const = 0;
};

using shared_object = std::shared_ptr<object>;
using object_list = std::vector<shared_object>;

#endif
