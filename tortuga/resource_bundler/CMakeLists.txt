cmake_minimum_required(VERSION 3.15)

project(resource_bundler
        VERSION 0.1
        LANGUAGES C CXX)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(resource_bundler_src
        main.hpp
        main.cpp)

add_executable(resource_bundler ${resource_bundler_src})

set_target_properties(resource_bundler PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)