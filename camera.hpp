#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "image.hpp"
#include "material.hpp"
#include "object.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "random.hpp"
#include "vec.hpp"

#include <cmath>
#include <iostream>
#include <numbers>
#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>

using std::numbers::pi;
using range = tbb::blocked_range<int>;

struct view
{
    point3 from, at;
    vec3 up;
    double field;

    double focus_dist;
    double focus_angle;

    color3 back_gnd{.7, .8, 1};
};

struct camera
{
    image render(const object& world, const view& view) const
    {
        auto h = std::tan(deg2rad(view.field) / 2);

        auto vp_height = 2 * h * view.focus_dist;
        auto vp_width = vp_height * width / height;

        auto w = unit(view.from - view.at);
        auto u = unit(cross(view.up, w));
        auto v = unit(cross(w, u));

        auto viewport0 = view.from + (-view.focus_dist * w) + (-vp_width / 2 * u) + (vp_height / 2 * v);

        auto focus_radius = view.focus_dist * std::tan(deg2rad(view.focus_angle / 2));
        auto focus_disk = [&]{ return focus_radius * rnd_disk3() * (u + v); };

        auto dx = vp_width / width * u;
        auto dy = -vp_height / height * v;

        auto pixel0 = viewport0 + .5 * (dx + dy);
        auto sub_pixel = [&]{ return (rnd_square3() - .5) * (dx + dy); };

        image image{width, height};

        auto ci = image.pixel.begin();
        for (int y = 0; y < height; ++y)
        {
            std::cerr << "\rRemaining: " << (height - y) << ' ' << std::flush;
            for (int x = 0; x < width; ++x)
            {
                auto pixel = pixel0 + (x * dx) + (y * dy);

                auto c = tbb::parallel_reduce(range{0, samples_per_pixel}, color3{ },
                    [&](const range& r, color3 c)
                    {
                        for (auto i = r.begin(); i != r.end(); ++i)
                        {
                            auto origin = view.from + focus_disk();
                            auto dir = pixel - origin + sub_pixel();
                            auto time = rnd();

                            c += ray_color(ray3{origin, dir, time}, max_depth, world, view.back_gnd);
                        }
                        return c;
                    },
                    [](const color3& x, const color3& y){ return x + y; }
                );

                *ci++ = sqrt(c / samples_per_pixel); // sqrt = gamma correction
            }
        }
        std::cerr << "\rDone.            " << std::endl;

        return image;
    }

private:
    int samples_per_pixel = 500;
    int max_depth = 50;

    int width = 1200;
    int height = width * 9 / 16;

    color3 ray_color(const ray3& ray, int depth, const object& world, const color3& back_gnd) const
    {
        if (!depth) return color3{ };

        auto hit = world.get_hit(ray, {.001, inf});
        if (!hit) return back_gnd;

        color3 color{ };

        if (auto emitted = hit->mat->get_emitted(hit->uv, hit->point))
            color += *emitted;

        if (auto scatter = hit->mat->get_scatter(ray, *hit))
            color += scatter->atten * ray_color(scatter->ray, --depth, world, back_gnd);

        return color;
    }

    constexpr static double deg2rad(double deg) { return deg * pi / 180; }
};

#endif
