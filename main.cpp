#include "camera.hpp"
#include "dielec.hpp"
#include "lambert.hpp"
#include "metal.hpp"
#include "object.hpp"
#include "point.hpp"
#include "random.hpp"
#include "sphere.hpp"

int main(int argc, char* argv[])
{
    object_list world;

    auto mat_ground = std::make_shared<lambert>(color3{.5, .5, .5});
    world.emplace_back(new sphere3{ point3{ 0, -1000, 0}, 1000, mat_ground });

    for (int a = -11; a < 11; ++a)
        for (int b = -11; b < 11; ++b)
        {
            auto choice = rnd();
            auto center = point3{a + .9 * rnd(), .2, b + .9 * rnd()};

            if (len(center - point3{4, .2, 0}) > .9)
            {
                if (choice < .8) // diffuse
                {
                    auto albedo = rnd_color3() * rnd_color3();
                    auto mat_sphere = std::make_shared<lambert>(albedo);
                    auto center1 = center + vec3{0, .5 * rnd(), 0};
                    world.emplace_back(new sphere3{center, center1, .2, mat_sphere});
                }
                else if (choice < .95) // metal
                {
                    auto albedo = (rnd_color3() + 1) / 2;
                    auto fuzz = rnd() / 2;
                    auto mat_sphere = std::make_shared<metal>(albedo, fuzz);
                    world.emplace_back(new sphere3{ center, .2, mat_sphere });
                }
                else // glass
                {
                    auto mat_sphere = std::make_shared<dielec>(1.5);
                    world.emplace_back(new sphere3{center, .2, mat_sphere});
                }
            }
        }

    auto mat1 = std::make_shared<dielec>(1.5);
    world.emplace_back(new sphere3{ point3{0, 1, 0}, 1, mat1 });

    auto mat2 = std::make_shared<lambert>(color3{.4, .2, .1});
    world.emplace_back(new sphere3{ point3{-4, 1, 0}, 1, mat2 });

    auto mat3 = std::make_shared<metal>(color3{.7, .6, .5}, 0);
    world.emplace_back(new sphere3{ point3{4, 1, 0}, 1, mat3 });

    view view;
    view.from  = point3{13, 2, 3};
    view.at    = point3{ 0, 0, 0};
    view.up    = vec3  { 0, 1, 0};
    view.field = 20;
    view.focus_angle = .6;
    view.focus_dist = 10;

    camera{ }.render(world, view);

    return 0;
}
