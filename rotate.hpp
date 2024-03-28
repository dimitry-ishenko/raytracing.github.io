#ifndef ROTATE_HPP
#define ROTATE_HPP

#include "math.hpp"
#include "object.hpp"

#include <cmath>
#include <memory>

struct rotate_y : object
{
    rotate_y(std::shared_ptr<object> child, double angle) :
        child{std::move(child)}, sin_th{std::sin(deg2rad(angle))}, cos_th{std::cos(deg2rad(angle))}
    {
        point3 pmin{ inf, inf, inf }, pmax{ -inf, -inf, -inf };

        bbox = this->child->bbox;
        for (auto x : { bbox.x.min, bbox.x.max })
            for (auto y : { bbox.y.min, bbox.y.max })
                for (auto z : { bbox.z.min, bbox.z.max })
                {
                    vec3 vec{ cos_th * x + sin_th * z, y, -sin_th * x + cos_th * z };
                    pmin = min(pmin, vec);
                    pmax = max(pmax, vec);
                }

        bbox = aabb{pmin, pmax};
    }

    virtual std::optional<hit> get_hit(const ray3& ray, interval ti) const override
    {
        vec3 origin
        {
            cos_th * ray.origin.x() - sin_th * ray.origin.z(),
            ray.origin.y(),
            sin_th * ray.origin.x() + cos_th * ray.origin.z()
        };
        vec3 dir
        {
            cos_th * ray.dir.x() - sin_th * ray.dir.z(),
            ray.dir.y(),
            sin_th * ray.dir.x() + cos_th * ray.dir.z()
        };

        auto hit = child->get_hit(ray3{origin, dir, ray.time}, ti);
        if (hit)
        {
            point3 point
            {
                cos_th * hit->point.x() + sin_th * hit->point.z(),
                hit->point.y(),
               -sin_th * hit->point.x() + cos_th * hit->point.z()
            };
            hit->point = point;

            vec3 norm
            {
                cos_th * hit->norm.x() + sin_th * hit->norm.z(),
                hit->norm.y(),
               -sin_th * hit->norm.x() + cos_th * hit->norm.z()
            };
            hit->norm = norm;
        }

        return hit;
    }

private:
    std::shared_ptr<object> child;
    double sin_th, cos_th;
};

#endif
