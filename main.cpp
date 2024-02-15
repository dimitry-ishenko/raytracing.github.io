#include "color.hpp"
#include "image.hpp"
#include "object.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vec.hpp"

#include <iostream>
#include <limits>

constexpr const auto inf = std::numeric_limits<double>::infinity();

auto ray_color(const ray3& ray, const object_list& world)
{
    static const color3 white{1, 1, 1}, blue{.5, .7, 1};

    if (auto hit = world.get_hit(ray, 0, inf); !hit)
    {
        auto t = unit(ray.dir).y() / 2 + .5;
        return lerp(white, blue, t);
    }
    else return color3::from_vec3(hit->norm / 2 + .5);
}

int main(int argc, char* argv[])
{
    int image_width = 1200, image_height = image_width * 9 / 16;

    object_list world;
    world.children.emplace_back(new sphere3{point3{0, 0, -1}, .5});
    world.children.emplace_back(new sphere3{point3{0, -100.5, -1}, 100});

    double viewport_height = 2;
    double viewport_width = viewport_height * image_width / image_height;

    point3 camera_0{0, 0, 0};
    double focal_len = 1;

    vec3 delta_u{ viewport_width / image_width, 0, 0 };
    vec3 delta_v{ 0, -viewport_height / image_height, 0 };

    auto viewport_0 = camera_0 + vec3{ -viewport_width / 2, viewport_height / 2, -focal_len };
    auto pixel_0 = viewport_0 + .5 * (delta_u + delta_v);

    image img{std::cout, image_width, image_height};

    for (int j = 0; j < img.height(); ++j)
    {
        std::cerr << "\rRemaining: " << (img.height() - j) << ' ' << std::flush;
        for (int i = 0; i < img.width(); ++i)
        {
            auto pixel = pixel_0 + (i * delta_u) + (j * delta_v);
            auto dir = pixel - camera_0;

            ray3 ray{camera_0, dir};
            img << ray_color(ray, world);
        }
    }
    std::cerr << "\rDone.            " << std::endl;

    return 0;
}