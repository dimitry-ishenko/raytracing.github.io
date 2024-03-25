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

    virtual std::optional<hit> get_hit(const ray3&, interval) const = 0;
};

using object_list = std::vector< std::shared_ptr<object> >;

inline void append(object_list& to, object_list from)
{
    for (auto& obj : from) to.push_back(std::move(obj));
}

#endif
