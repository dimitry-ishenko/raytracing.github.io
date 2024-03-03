#include "camera.hpp"
#include "object.hpp"
#include "point.hpp"
#include "sphere.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    object_list world;
    world.children.emplace_back(new sphere3{point3{0, 0, -1}, .5});
    world.children.emplace_back(new sphere3{point3{0, -100.5, -1}, 100});

    int width = 1200, height = width * 9 / 16;
    camera{ }.render(world, width, height);

    return 0;
}
