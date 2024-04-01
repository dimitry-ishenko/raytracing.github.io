#ifndef ISOTROPIC_HPP
#define ISOTROPIC_HPP

#include "color.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "random.hpp"
#include "solid.hpp"
#include "texture.hpp"

#include <memory>

struct isotropic : material
{
    explicit isotropic(const color3& c) : isotropic{std::make_shared<solid>(c)} { }
    explicit isotropic(std::shared_ptr<texture> tex) : tex{std::move(tex)} { }

    virtual std::optional<scatter> get_scatter(const ray3& ray, const hit& hit) const override
    {
        auto dir = unit(rnd_sphere3());
        return scatter{ ray3{hit.point, dir, ray.time}, tex->value(hit.uv, hit.point) };
    }

private:
    std::shared_ptr<texture> tex;
};

#endif
