cmake_minimum_required(VERSION 3.16) # focal
project(ex VERSION 2.3.11)

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
    color.hpp
    dielec.hpp
    hit.hpp
    interval.hpp
    lambert.hpp
    main.cpp
    material.hpp
    metal.hpp
    object.hpp
    point.hpp
    random.hpp
    ray.hpp
    sphere.hpp
    vec.hpp
)
target_compile_options(${EX} PUBLIC -O3)
target_link_libraries(${EX} PUBLIC tbb)
