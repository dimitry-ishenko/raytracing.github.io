#ifndef DIELEC_HPP
#define DIELEC_HPP

#include "color.hpp"
#include "object.hpp" // hit
#include "material.hpp"
#include "vec.hpp"

#include <cmath> // std::abs

struct dielec : material
{
    double ri;

    explicit dielec(double ri) : ri{ri} { }

    virtual std::optional<scatter> get_scatter(const ray3& ray, const hit& hit) const override
    {
        auto dir = refract(unit{ray.dir}, hit.norm, hit.front ? 1 / ri : ri);
        return scatter{ ray3{hit.point, dir}, color3{1, 1, 1} };
    }

private:
    static vec3 refract(const unit<vec3>& l, const unit<vec3>& n, double ri)
    {
        // https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
        auto cos_th1 = dot(-n, l);
        auto cos_th2 = std::sqrt(std::abs(1 - ri * ri * (1 - cos_th1 * cos_th1)));
        return ri * l + (ri * cos_th1 - cos_th2) * n;
    }
};

#endif
