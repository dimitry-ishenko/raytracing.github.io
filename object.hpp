#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "aabb.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "ray.hpp"

#include <memory>
#include <vector>

struct object
{
    aabb bbox;

    virtual optional_hit get_hit(const ray3&, interval) const = 0;
};

using shared_object = std::shared_ptr<object>;
using object_list = std::vector<shared_object>;

#endif
