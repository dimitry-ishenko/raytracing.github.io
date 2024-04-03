#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "color.hpp"
#include "hit.hpp"
#include "isotropic.hpp"
#include "material.hpp"
#include "object.hpp"
#include "random.hpp"
#include "solid.hpp"

#include <cmath> // std::log
#include <memory>

struct constant : object
{
    constant(std::shared_ptr<object> edge, double dense, const color3& color) :
        constant{std::move(edge), dense, std::make_shared<solid>(color)}
    { }

    constant(std::shared_ptr<object> edge, double dense, std::shared_ptr<texture> tex) :
        edge{std::move(edge)}, dense{dense}, mat{std::make_shared<isotropic>(tex)}
    {
        bbox = this->edge->bbox;
    }

    virtual std::optional<hit> get_hit(const ray3& ray, interval ti) const override
    {
        auto hit1 = edge->get_hit(ray, interval{-inf, +inf});
        if (!hit1) return { };

        auto hit2 = edge->get_hit(ray, interval{hit1->t + .0001, +inf});
        if (!hit2) return { };

        if (hit1->t < ti.min) hit1->t = ti.min;
        if (hit2->t > ti.max) hit2->t = ti.max;

        if (hit1->t >= hit2->t) return { };
        if (hit1->t < 0) hit1->t = 0;

        auto dist = hit2->t - hit1->t;
        auto hit_dist = -std::log(rnd()) / dense / len(ray.dir);
        if (hit_dist > dist) return { };

        auto t = hit1->t + hit_dist;
        auto point= ray.at(t);
        auto norm = vec3{1, 0, 0}; // arbitrary
        auto front= true; // arbitrary

        return hit{ point, norm, t, front, mat };
    }

private:
    std::shared_ptr<object> edge;
    double dense;
    std::shared_ptr<material> mat;
};

#endif
