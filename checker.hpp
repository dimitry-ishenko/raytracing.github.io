#ifndef CHECKER_HPP
#define CHECKER_HPP

#include "color.hpp"
#include "point.hpp"
#include "solid.hpp"
#include "texture.hpp"

#include <cmath> // std::floor
#include <memory>

struct checker : texture
{
    checker(double scale, color3 even, color3 odd) :
        scale{scale}, even{std::make_shared<solid>(std::move(even))}, odd{std::make_shared<solid>(std::move(odd))}
    { }

    checker(double scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd) :
        scale{scale}, even{std::move(even)}, odd{std::move(odd)}
    { }

    virtual color3 value(const point2& uv, const point3& p) const override
    {
#if 0
        int ix = std::floor(p.x() / scale);
        int iy = std::floor(p.y() / scale);
        int iz = std::floor(p.z() / scale);
#else
        int ix = std::floor(uv.x() / scale);
        int iy = std::floor(uv.y() / scale);
        int iz = 0;
#endif
        auto s = (ix + iy + iz) % 2;
        return s ? even->value(uv, p) : odd->value(uv, p);
    }

private:
    double scale;
    std::shared_ptr<texture> even, odd;
};

#endif
