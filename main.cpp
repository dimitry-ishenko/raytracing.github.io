#include "camera.hpp"
#include "dielec.hpp"
#include "lambert.hpp"
#include "metal.hpp"
#include "object.hpp"
#include "point.hpp"
#include "sphere.hpp"

int main(int argc, char* argv[])
{
    auto mat_ground = std::make_shared<lambert>(color3{.8, .8,  0});
    auto mat_center = std::make_shared<lambert>(color3{.1, .2, .5});
    auto mat_left   = std::make_shared<dielec >(1.5);
    auto mat_right  = std::make_shared<metal  >(color3{.8, .6, .2}, 0);

    object_list world;
    world.children.emplace_back(new sphere3{ point3{ 0, -100.5, -1}, 100, mat_ground });
    world.children.emplace_back(new sphere3{ point3{ 0,      0, -1},  .5, mat_center });
    world.children.emplace_back(new sphere3{ point3{-1,      0, -1},  .5, mat_left   });
    world.children.emplace_back(new sphere3{ point3{-1,      0, -1}, -.4, mat_left   });
    world.children.emplace_back(new sphere3{ point3{ 1,      0, -1},  .5, mat_right  });

    view view;
    view.from  = point3{-2, 2,  1};
    view.at    = point3{ 0, 0, -1};
    view.up    = vec3  { 0, 1,  0};
    view.field = 20;

    camera{ }.render(world, view);

    return 0;
}
