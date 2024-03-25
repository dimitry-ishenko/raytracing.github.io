#include "bvh.hpp"
#include "camera.hpp"
#include "checker.hpp"
#include "color.hpp"
#include "dielec.hpp"
#include "diffuse.hpp"
#include "image.hpp"
#include "lambert.hpp"
#include "metal.hpp"
#include "noise.hpp"
#include "object.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "quad.hpp"
#include "random.hpp"
#include "sphere.hpp"
#include "texture.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path>\n";
        return 1;
    }

    object_list world;
    view view;

#if 0 // motion
    auto tex = std::make_shared<checker>(.32, color3{.2, .3, .1}, color3{.9, .9, .9});
    world.push_back(std::make_shared<sphere3>( point3{0, -1000, 0}, 1000, std::make_shared<lambert>(tex) ));

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
                    auto center1 = center + vec3{0, .5 * rnd(), 0};
                    world.push_back(std::make_shared<sphere3>( center, center1, .2, std::make_shared<lambert>(albedo) ));
                }
                else if (choice < .95) // metal
                {
                    auto albedo = (rnd_color3() + 1) / 2;
                    auto fuzz = rnd() / 2;
                    world.push_back(std::make_shared<sphere3>( center, .2, std::make_shared<metal>(albedo, fuzz) ));
                }
                else // glass
                {
                    world.push_back(std::make_shared<sphere3>( center, .2, std::make_shared<dielec>(1.5) ));
                }
            }
        }

    world.push_back(std::make_shared<sphere3>( point3{ 0, 1, 0}, 1, std::make_shared<dielec >(1.5) ));
    world.push_back(std::make_shared<sphere3>( point3{-4, 1, 0}, 1, std::make_shared<lambert>(color3{.4, .2, .1}) ));
    world.push_back(std::make_shared<sphere3>( point3{ 4, 1, 0}, 1, std::make_shared<metal  >(color3{.7, .6, .5}, 0) ));

    view.from  = point3{13, 2, 3};
    view.at    = point3{ 0, 0, 0};
    view.up    = vec3  { 0, 1, 0};
    view.field = 20;
    view.focus_angle = .6;
    view.focus_dist = 10;
#endif

#if 0 // checker
    auto tex = std::make_shared<checker>(.032, color3{.2, .3, .1}, color3{.9, .9, .9});

    world.push_back(std::make_shared<sphere3>( point3{0, -10, 0}, 10, std::make_shared<lambert>(tex) ));
    world.push_back(std::make_shared<sphere3>( point3{0,  10, 0}, 10, std::make_shared<lambert>(tex) ));

    view.from  = point3{13, 2, 3};
    view.at    = point3{ 0, 0, 0};
    view.up    = vec3  { 0, 1, 0};
    view.field = 20;
    view.focus_angle = 0;
    view.focus_dist = 10;
#endif

#if 0 // earth
    auto tex = std::make_shared<pixmap>("./image/earthmap.ppm");
    world.push_back(std::make_shared<sphere3>( point3{0, 0, 0}, 2, std::make_shared<lambert>(tex) ));

    view.from  = point3{0, 8, -9};
    view.at    = point3{0, 0,  0};
    view.up    = vec3  {0, 1,  0};
    view.field = 20;
    view.focus_angle = 0;
    view.focus_dist = 10;
#endif

#if 0 // perlin
    auto tex = std::make_shared<noise>(4);
    world.push_back(std::make_shared<sphere3>( point3{0, -1000, 0}, 1000, std::make_shared<lambert>(tex) ));
    world.push_back(std::make_shared<sphere3>( point3{0,     2, 0},    2, std::make_shared<lambert>(tex) ));

    view.from  = point3{13, 2, 3};
    view.at    = point3{ 0, 0, 0};
    view.up    = vec3  { 0, 1, 0};
    view.field = 20;
    view.focus_angle = 0;
    view.focus_dist = 10;
#endif

#if 0 // quad
    auto red    = std::make_shared<lambert>(color3{ 1, .2, .2});
    auto green  = std::make_shared<lambert>(color3{.2,  1, .2});
    auto blue   = std::make_shared<lambert>(color3{.2, .2,  1});
    auto orange = std::make_shared<lambert>(color3{ 1, .5,  0});
    auto teal   = std::make_shared<lambert>(color3{.2, .8, .8});

    world.push_back(std::make_shared<quad>( point3{-3, -2, 5}, vec3{0, 0,-4}, vec3{0, 4, 0}, red    ));
    world.push_back(std::make_shared<quad>( point3{-2, -2, 0}, vec3{4, 0, 0}, vec3{0, 4, 0}, green  ));
    world.push_back(std::make_shared<quad>( point3{ 3, -2, 1}, vec3{0, 0, 4}, vec3{0, 4, 0}, blue   ));
    world.push_back(std::make_shared<quad>( point3{-2,  3, 1}, vec3{4, 0, 0}, vec3{0, 0, 4}, orange ));
    world.push_back(std::make_shared<quad>( point3{-2, -3, 5}, vec3{4, 0, 0}, vec3{0, 0,-4}, teal   ));

    view.from  = point3{0, 0, 9};
    view.at    = point3{0, 0, 0};
    view.up    = vec3  {0, 1, 0};
    view.field = 80;
    view.focus_angle = 0;
    view.focus_dist = 10;
#endif

#if 0 // light
    auto tex = std::make_shared<noise>(4);
    world.push_back(std::make_shared<sphere3>( point3{0, -1000, 0}, 1000, std::make_shared<lambert>(tex) ));
    world.push_back(std::make_shared<sphere3>( point3{0, 2, 0}, 2, std::make_shared<lambert>(tex) ));

    auto light = std::make_shared<diffuse>(color3{4, 4, 4});
    world.push_back(std::make_shared<sphere3>( point3{0, 7, -0}, 2, light ));
    world.push_back(std::make_shared<quad>( point3{3, 1, -2}, vec3{2, 0, 0}, vec3{0, 2, 0}, light ));

    view.from  = point3{26, 3, 6};
    view.at    = point3{ 0, 2, 0};
    view.up    = vec3  { 0, 1, 0};
    view.field = 20;
    view.focus_angle = 0;
    view.focus_dist = 10;

    view.back_gnd = color3{0, 0, 0};
#endif

#if 1 // cornell box
    auto green = std::make_shared<lambert>( color3{.12, .45, .15} );
    auto red   = std::make_shared<lambert>( color3{.65, .05, .05} );
    auto white = std::make_shared<lambert>( color3{.73, .73, .73} );
    auto light = std::make_shared<diffuse>( color3{15., 15., 15.} );

    world.push_back(std::make_shared<quad>( point3{555,   0,   0}, vec3{   0, 555, 0}, vec3{0,   0,  555}, green ));
    world.push_back(std::make_shared<quad>( point3{  0,   0,   0}, vec3{   0, 555, 0}, vec3{0,   0,  555}, red   ));
    world.push_back(std::make_shared<quad>( point3{343, 554, 332}, vec3{-130,   0, 0}, vec3{0,   0, -105}, light ));
    world.push_back(std::make_shared<quad>( point3{  0,   0,   0}, vec3{ 555,   0, 0}, vec3{0,   0,  555}, white ));
    world.push_back(std::make_shared<quad>( point3{555, 555, 555}, vec3{-555,   0, 0}, vec3{0,   0, -555}, white ));
    world.push_back(std::make_shared<quad>( point3{  0,   0, 555}, vec3{ 555,   0, 0}, vec3{0, 555,    0}, white ));

    view.from  = point3{278, 278, -800};
    view.at    = point3{278, 278,    0};
    view.up    = vec3{ 0, 1, 0};
    view.field = 40;
    view.focus_angle = 0;
    view.focus_dist = 10;

    view.back_gnd = color3{0, 0, 0};
#endif

    auto image = camera{ }.render(bvh_node{std::move(world)}, view);
    image.save_to(argv[1]);

    return 0;
}
