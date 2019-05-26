cmake_minimum_required(VERSION 3.14)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(ong_src
        ball.hpp
        main.cpp
        player.hpp
        menu_screen.hpp
        game_screen.hpp)

add_executable(ong ${ong_src})

set_target_properties(ong PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(ong
        PUBLIC
            utils
            ${SFML_LIB_INCLUDE})

target_link_directories(ong
        PUBLIC
            ${SFML_LIB_PATH})

target_link_libraries(ong
        PUBLIC
            utils
            sfml-graphics
            sfml-window
            sfml-system)