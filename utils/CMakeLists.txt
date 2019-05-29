cmake_minimum_required(VERSION 3.14)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(utils_src
        math/mat3.hpp
        math/mat3.cpp
        math/vector.hpp
        math/math.hpp
        math/math.cpp
        screen/screen.cpp
        screen/screen.hpp
        screen/screen_manager.cpp
        screen/screen_manager.hpp)

add_library(utils ${utils_src})

set_target_properties(utils PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(utils
        PUBLIC
            ${SFML_LIB_INCLUDE})

target_link_directories(utils
        PUBLIC
            ${SFML_LIB_PATH})

target_link_libraries(utils
        PUBLIC
            sfml-graphics
            sfml-window
            sfml-system
            sfml-audio)