#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "object.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "random.hpp"
#include "vec.hpp"

#include <algorithm> // std::clamp
#include <cmath> // std::lerp
#include <execution>
#include <iostream>
#include <numeric> // std::transform_reduce
#include <ranges>

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

    int width_, height_;
    point3 center_{0, 0, 0};
    double focal_len_ = 1;
    int samples_ = 100;

public:
    camera(int width, int height) : width_{width}, height_{height} { }

    void render(const object_list& world) const
    {
        double viewport_height = 2;
        double viewport_width = viewport_height * width_ / height_;

        auto viewport0 = center_ + vec3{ -viewport_width / 2, viewport_height / 2, -focal_len_ };

        auto dx = vec3{ viewport_width / width_, 0, 0 };
        auto dy = vec3{ 0, -viewport_height / height_, 0 };
        auto pixel0 = viewport0 + .5 * (dx + dy);

        rnd_gen rnd{-.5, .5};

        std::cout << "P3\n" << width_ << ' ' << height_ << "\n255\n";

        for (int j = 0; j < height_; ++j)
        {
            std::cerr << "\rRemaining: " << (height_ - j) << ' ' << std::flush;
            for (int i = 0; i < width_; ++i)
            {
                auto pixel = pixel0 + (i * dx) + (j * dy);
                auto dir = pixel - center_;

                auto s = std::views::iota(0, samples_);
                auto c = std::transform_reduce(std::execution::par_unseq,
                    s.begin(), s.end(), color3{0, 0, 0}, std::plus<>(), [&](auto)
                    {
                        auto sub_pix = dx * rnd() + dy * rnd();
                        return ray_color(ray3{center_, dir + sub_pix}, world);
                    }
                ) / s.size();

                std::cout << to_8bit(c.r()) << ' ' << to_8bit(c.g()) << ' ' << to_8bit(c.b()) << '\n';
            }
        }
        std::cerr << "\rDone.            " << std::endl;
    }
};

#endif
