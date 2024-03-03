#ifndef DIELEC_HPP
#define DIELEC_HPP

#include "color.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "vec.hpp"

#include <cmath>

struct dielec : material
{
    explicit dielec(double refrac) : refrac{refrac} { }

    virtual optional_scatter get_scatter(const ray3& ray, const hit& hit) const override
    {
        // https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
        auto l = unit(ray.dir);
        auto n = hit.norm;
        auto r_idx = hit.front ? 1 / refrac : refrac;

        auto cos_th1 = dot(-n, l);
        auto sin2_th2 = r_idx * r_idx * (1 - cos_th1 * cos_th1);

        // https://en.wikipedia.org/wiki/Schlick%27s_approximation
        auto r0 = (1 - r_idx) / (1 + r_idx);
        r0 = r0 * r0;
        auto r_th = r0 + (1 - r0) * std::pow(1 - cos_th1, 5);

        vec3 ref;
        if (sin2_th2 > 1 || r_th > rnd()) // reflect
        {
            ref = l + 2 * cos_th1 * n;
        }
        else // refract
        {
            auto cos_th2 = std::sqrt(1 - sin2_th2);
            ref = r_idx * l + (r_idx * cos_th1 - cos_th2) * n;
        }

        return scatter{ ray3{hit.point, ref, ray.time}, color3{1, 1, 1} };
    }

private:
    double refrac;
};

#endif
