cmake_minimum_required(VERSION 3.14)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(pong_src
        src/ball.hpp
        src/pong.hpp
        src/vec2.hpp
        src/mat3.hpp
        src/main.cpp
        src/player.hpp
        src/math.hpp)

SET(SFML_LIB_PATH "C:\\Program\ Files\ (x86)\\SFML\\lib")
SET(SFML_LIB_INCLUDE "C:\\Program\ Files\ (x86)\\SFML\\include")

add_executable(pong ${pong_src})

target_include_directories(pong
        PUBLIC
            ${SFML_LIB_INCLUDE})

target_link_directories(pong
        PUBLIC
            ${SFML_LIB_PATH})

target_link_libraries(pong
        PUBLIC
            sfml-graphics
            sfml-window
            sfml-system)