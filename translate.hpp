#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#include "object.hpp"
#include "ray.hpp"
#include "vec.hpp"

#include <memory>

struct translate : object
{
    translate(std::shared_ptr<object> child, vec3 diff) :
        child{std::move(child)}, diff{std::move(diff)}
    {
        bbox = this->child->bbox + diff;
    }

    virtual std::optional<hit> get_hit(const ray3& ray, interval ti) const override
    {
        auto hit = child->get_hit(ray3{ray.origin - diff, ray.dir, ray.time}, ti);
        if (hit) hit->point += diff;

        return hit;
    }

private:
    std::shared_ptr<object> child;
    vec3 diff;
};

#endif
