#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "material.hpp"
#include "solid.hpp"
#include "texture.hpp"

#include <memory>

struct diffuse : material
{
    explicit diffuse(color3 color) :
        tex{std::make_shared<solid>(std::move(color))}
    { }

    explicit diffuse(std::shared_ptr<texture> tex) :
        tex{std::move(tex)}
    { }

    virtual std::optional<color3> get_emitted(const point2& uv, const point3& p) const override
    {
        return tex->value(uv, p);
    }

private:
    std::shared_ptr<texture> tex;
};

#endif
