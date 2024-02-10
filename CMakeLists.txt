cmake_minimum_required(VERSION 3.16) # focal
project(ex VERSION 1.08)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}-${PROJECT_VERSION}
    array.hpp
    camera.hpp
    color.hpp
    interval.hpp
    main.cpp
    object.hpp
    point.hpp
    random.hpp
    ray.hpp
    sphere.hpp
    vec.hpp
)
