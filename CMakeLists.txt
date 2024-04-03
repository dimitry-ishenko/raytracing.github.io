cmake_minimum_required(VERSION 3.16) # focal
project(ex VERSION 2.9.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EX ${PROJECT_NAME}-${PROJECT_VERSION})
add_executable(${EX}
    aabb.hpp
    array.hpp
    box.hpp
    bvh.hpp
    camera.hpp
    checker.hpp
    color.hpp
    constant.hpp
    dielec.hpp
    diffuse.hpp
    hit.hpp
    image.hpp
    interval.hpp
    isotropic.hpp
    lambert.hpp
    main.cpp
    material.hpp
    math.hpp
    metal.hpp
    noise.hpp
    object.hpp
    perlin.hpp
    pixmap.hpp
    point.hpp
    quad.hpp
    random.hpp
    ray.hpp
    rotate.hpp
    solid.hpp
    sphere.hpp
    texture.hpp
    translate.hpp
    vec.hpp
)
target_link_libraries(${EX} PUBLIC tbb)
