#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "object.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vec.hpp"

#include <algorithm> // std::clamp
#include <cmath> // std::lerp
#include <iostream>

class camera
{
    static auto ray_color(const ray3& ray, const object_list& world)
    {
        static const color3 white{1, 1, 1}, blue{.5, .7, 1};

        auto hit = world.get_hit(ray, {0, inf});
        if (hit) return color3::from_vec3(hit->norm / 2 + .5);

        auto t = unit(ray.dir).y() / 2 + .5;
        return lerp(white, blue, t);
    }

    constexpr static int to_8bit(double v) { return std::lerp(0., 255., std::clamp(v, 0., 1.)) + .5; }

public:
    void render(const object_list& world, int width, int height) const
    {
        point3 center{0, 0, 0};
        double focal_len = 1;

        double viewport_height = 2;
        double viewport_width = viewport_height * width / height;

        auto viewport0 = center + vec3{ -viewport_width / 2, viewport_height / 2, -focal_len };

        auto dx = vec3{ viewport_width / width, 0, 0 };
        auto dy = vec3{ 0, -viewport_height / height, 0 };
        auto pixel0 = viewport0 + .5 * (dx + dy);

        std::cout << "P3\n" << width << ' ' << height << "\n255\n";

        for (int j = 0; j < height; ++j)
        {
            std::cerr << "\rRemaining: " << (height - j) << ' ' << std::flush;
            for (int i = 0; i < width; ++i)
            {
                auto pixel = pixel0 + (i * dx) + (j * dy);
                auto dir = pixel - center;

                auto c = ray_color(ray3{center, dir}, world);
                std::cout << to_8bit(c.r()) << ' ' << to_8bit(c.g()) << ' ' << to_8bit(c.b()) << '\n';
            }
        }
        std::cerr << "\rDone.            " << std::endl;
    }
};

#endif
