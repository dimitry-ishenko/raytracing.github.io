#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "material.hpp"
#include "object.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "random.hpp"
#include "vec.hpp"

#include <algorithm> // std::clamp
#include <cmath>
#include <iostream>
#include <numbers>
#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>

using range = tbb::blocked_range<int>;

struct view
{
    point3 from, at;
    vec3 up;
    double field;

    double focus_dist;
    double focus_angle;
};

struct camera
{
    int samples_per_pixel = 500;
    int max_depth = 50;

    int img_width = 1200;
    int img_height = img_width * 9 / 16;

    void render(const object& world, const view& view) const
    {
        auto h = std::tan(deg2rad(view.field) / 2);

        auto vp_height = 2 * h * view.focus_dist;
        auto vp_width = vp_height * img_width / img_height;

        auto w = unit(view.from - view.at);
        auto u = unit(cross(view.up, w));
        auto v = unit(cross(w, u));

        auto viewport0 = view.from + (-view.focus_dist * w) + (-vp_width / 2 * u) + (vp_height / 2 * v);

        auto focus_radius = view.focus_dist * std::tan(deg2rad(view.focus_angle / 2));
        auto focus_disk = [&]{ return focus_radius * rnd_disk3() * (u + v); };

        auto dx = vp_width / img_width * u;
        auto dy = -vp_height / img_height * v;

        auto pixel0 = viewport0 + .5 * (dx + dy);
        auto sub_pixel = [&]{ return (rnd_square3() - .5) * (dx + dy); };

        std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

        for (int j = 0; j < img_height; ++j)
        {
            std::cerr << "\rRemaining: " << (img_height - j) << ' ' << std::flush;
            for (int i = 0; i < img_width; ++i)
            {
                auto pixel = pixel0 + (i * dx) + (j * dy);

                auto c = tbb::parallel_reduce(range{0, samples_per_pixel}, color3{ },
                    [&](const range& r, color3 c)
                    {
                        for (auto i = r.begin(); i != r.end(); ++i)
                        {
                            auto origin = view.from + focus_disk();
                            auto dir = pixel - origin + sub_pixel();
                            auto time = rnd();

                            c += ray_color(ray3{origin, dir, time}, max_depth, world);
                        }
                        return c;
                    },
                    [](const color3& x, const color3& y){ return x + y; }
                ) / samples_per_pixel;

                c = sqrt(c); // gamma correction

                std::cout << to_8bit(c.r()) << ' ' << to_8bit(c.g()) << ' ' << to_8bit(c.b()) << '\n';
            }
        }
        std::cerr << "\rDone.            " << std::endl;
    }

private:
    static color3 ray_color(const ray3& ray, int depth, const object& world)
    {
        if (!depth) return { };

        if (auto hit = world.get_hit(ray, {.001, inf}))
        {
            if (auto scatter = hit->mat->get_scatter(ray, *hit))
                return scatter->atten * ray_color(scatter->ray, --depth, world);

            return { };
        }

        static constexpr color3 white{1, 1, 1}, blue{.5, .7, 1};

        auto t = unit(ray.dir).y() / 2 + .5;
        return lerp(white, blue, t);
    }

    constexpr static int to_8bit(double v) { return std::lerp(0., 255., std::clamp(v, 0., 1.)) + .5; }

    constexpr static double deg2rad(double deg) { return deg * std::numbers::pi / 180; }
};

#endif
