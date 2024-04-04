#include "box.hpp"
#include "bvh.hpp"
#include "camera.hpp"
#include "checker.hpp"
#include "color.hpp"
#include "constant.hpp"
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
#include "rotate.hpp"
#include "sphere.hpp"
#include "texture.hpp"
#include "translate.hpp"

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

#if 0 // cornell box
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

    auto box1 = box(point3{0, 0, 0}, point3{165, 330, 165}, white);
    box1 = std::make_shared<rotate_y>(box1, 15);
    box1 = std::make_shared<translate>(box1, vec3{265, 0, 295});
    world.push_back(box1);

    auto box2 = box(point3{0, 0, 0}, point3{165, 165, 165}, white);
    box2 = std::make_shared<rotate_y>(box2, -18);
    box2 = std::make_shared<translate>(box2, vec3{130, 0, 65});
    world.push_back(box2);

    view.from  = point3{278, 278, -800};
    view.at    = point3{278, 278,    0};
    view.up    = vec3{ 0, 1, 0};
    view.field = 40;
    view.focus_angle = 0;
    view.focus_dist = 10;

    view.back_gnd = color3{0, 0, 0};
#endif

#if 0 // cornell smoke
    auto green = std::make_shared<lambert>( color3{.12, .45, .15} );
    auto red   = std::make_shared<lambert>( color3{.65, .05, .05} );
    auto white = std::make_shared<lambert>( color3{.73, .73, .73} );
    auto light = std::make_shared<diffuse>( color3{  7,   7,   7} );

    world.push_back(std::make_shared<quad>( point3{555,   0,   0}, vec3{  0, 555, 0}, vec3{0,   0, 555}, green ));
    world.push_back(std::make_shared<quad>( point3{  0,   0,   0}, vec3{  0, 555, 0}, vec3{0,   0, 555}, red   ));
    world.push_back(std::make_shared<quad>( point3{113, 554, 127}, vec3{330,   0, 0}, vec3{0,   0, 305}, light ));
    world.push_back(std::make_shared<quad>( point3{  0, 555,   0}, vec3{555,   0, 0}, vec3{0,   0, 555}, white ));
    world.push_back(std::make_shared<quad>( point3{  0,   0,   0}, vec3{555,   0, 0}, vec3{0,   0, 555}, white ));
    world.push_back(std::make_shared<quad>( point3{  0,   0, 555}, vec3{555,   0, 0}, vec3{0, 555,   0}, white ));

    auto box1 = box(point3{0, 0, 0}, point3{165, 330, 165}, white);
    box1 = std::make_shared<rotate_y >(box1, 15);
    box1 = std::make_shared<translate>(box1, vec3{265, 0, 295});
    box1 = std::make_shared<constant >(box1, .01, color3{0, 0, 0});
    world.push_back(box1);

    auto box2 = box(point3{0, 0, 0}, point3{165, 165, 165}, white);
    box2 = std::make_shared<rotate_y >(box2, -18);
    box2 = std::make_shared<translate>(box2, vec3{130, 0, 65});
    box2 = std::make_shared<constant >(box2, .01, color3{1, 1, 1});
    world.push_back(box2);

    view.from  = point3{278, 278, -800};
    view.at    = point3{278, 278,    0};
    view.up    = vec3{ 0, 1, 0};
    view.field = 40;
    view.focus_angle = 0;
    view.focus_dist = 10;

    view.back_gnd = color3{0, 0, 0};
#endif

#if 1 // final scene
    auto ground = std::make_shared<lambert>(color3{.48, .83, .53});

    for (auto i = 0; i < 20; ++i)
        for (auto j = 0; j < 20; ++j)
        {
            constexpr auto w = 100;

            auto x0 = -1000. + i * w;
            auto y0 = 0.;
            auto z0 = -1000. + j * w;

            auto x1 = x0 + w;
            auto y1 = 1. + 100 * rnd();
            auto z1 = z0 + w;

            world.push_back( box(point3{x0, y0, z0}, point3{x1, y1, z1}, ground) );
        }

    auto light = std::make_shared<diffuse>( color3{7, 7, 7} );
    world.push_back(std::make_shared<quad>( point3{123, 554, 147}, vec3{300, 0, 0}, vec3{0, 0, 265}, light ));

    auto center1 = point3{400, 400, 200};
    auto center2 = center1 + vec3{30, 0, 0};
    auto matte = std::make_shared<lambert>(color3{.7, .3, .1});
    world.push_back(std::make_shared<sphere3>( center1, center2, 50, matte ));

    auto glass = std::make_shared<dielec>(1.5);
    world.push_back(std::make_shared<sphere3>( point3{260, 150, 45}, 50, glass ));

    auto metalic = std::make_shared<metal>( color3{.8, .8, .9}, 1 );
    world.push_back(std::make_shared<sphere3>( point3{0, 150, 145}, 50, metalic ));

    auto edge = std::make_shared<sphere3>( point3{360, 150, 145}, 70, glass );
    world.push_back(edge);
    world.push_back(std::make_shared<constant>( edge, .2, color3{.2, .4, .9} ));

    edge = std::make_shared<sphere3>( point3{0, 0, 0}, 5000, glass );
    world.push_back(std::make_shared<constant>( edge, .0001, color3{1, 1, 1} ));

    auto map = std::make_shared<lambert>(std::make_shared<pixmap>("./image/earthmap.ppm"));
    world.push_back(std::make_shared<sphere3>( point3{400, 200, 400}, 100, map ));

    auto perlin = std::make_shared<lambert>(std::make_shared<noise>(.2));
    world.push_back(std::make_shared<sphere3>( point3{220, 280, 300}, 80, perlin ));

    object_list spheres;
    auto white = std::make_shared<lambert>(color3{.73, .73, .73});
    for (auto i = 0; i < 1000; ++i)
    {
        auto center = 165 * point3{rnd(), rnd(), rnd()};
        spheres.push_back(std::make_shared<sphere3>(center, 10, white));
    }

    auto node = std::make_shared<bvh_node>(spheres);
    world.push_back(std::make_shared<translate>( std::make_shared<rotate_y>(node, 15), vec3{-100, 270, 395} ));

    view.from  = point3{478, 278, -600};
    view.at    = point3{278, 278,    0};
    view.up    = vec3{0, 1, 0};
    view.field = 40;
    view.focus_angle = 0;
    view.focus_dist = 10;

    view.back_gnd = color3{0, 0, 0};

    view.height = view.width;
    view.samples_per_pixel = 10000;
#endif

    auto image = camera{ }.render(bvh_node{std::move(world)}, view);
    image.save_to(argv[1]);

    return 0;
}
