cmake_minimum_required(VERSION 3.16) # focal
project(ex VERSION 1.02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}-${PROJECT_VERSION}
    array.hpp
    color.hpp
    image.hpp
    main.cpp
    ray.hpp
    types.hpp
    vec.hpp
)
