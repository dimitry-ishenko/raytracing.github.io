cmake_minimum_required(VERSION 3.16) # focal
project(ex VERSION 2.7.3.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EX ${PROJECT_NAME}-${PROJECT_VERSION})
add_executable(${EX}
    aabb.hpp
    array.hpp
    bvh.hpp
    camera.hpp
    checker.hpp
    color.hpp
    dielec.hpp
    diffuse.hpp
    hit.hpp
    image.hpp
    interval.hpp
    lambert.hpp
    main.cpp
    material.hpp
    metal.hpp
    noise.hpp
    object.hpp
    perlin.hpp
    pixmap.hpp
    point.hpp
    quad.hpp
    random.hpp
    ray.hpp
    solid.hpp
    sphere.hpp
    texture.hpp
    vec.hpp
)
target_link_libraries(${EX} PUBLIC tbb)
