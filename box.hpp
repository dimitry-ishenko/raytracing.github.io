#ifndef BOX_HPP
#define BOX_HPP

#include "bvh.hpp"
#include "material.hpp"
#include "object.hpp"
#include "point.hpp"
#include "quad.hpp"

#include <cmath>
#include <memory>

inline std::shared_ptr<object> box(const point3& a, const point3& b, std::shared_ptr<material> mat)
{
    auto [x0, x1] = std::minmax({ a.x(), b.x() });
    auto [y0, y1] = std::minmax({ a.y(), b.y() });
    auto [z0, z1] = std::minmax({ a.z(), b.z() });

    vec3 dx{x1 - x0, 0, 0};
    vec3 dy{0, y1 - y0, 0};
    vec3 dz{0, 0, z1 - z0};

    object_list box;

    box.push_back(std::make_shared<quad>( point3{x0, y0, z1},  dx,  dy, mat ));
    box.push_back(std::make_shared<quad>( point3{x1, y0, z1}, -dz,  dy, mat ));
    box.push_back(std::make_shared<quad>( point3{x1, y0, z0}, -dx,  dy, mat ));
    box.push_back(std::make_shared<quad>( point3{x0, y0, z0},  dz,  dy, mat ));
    box.push_back(std::make_shared<quad>( point3{x0, y1, z1},  dx, -dz, mat ));
    box.push_back(std::make_shared<quad>( point3{x0, y0, z0},  dx,  dz, mat ));

    return std::make_shared<bvh_node>(std::move(box));
}

#endif
