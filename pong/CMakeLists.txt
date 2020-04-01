cmake_minimum_required(VERSION 3.15)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(pong_src
        ball.hpp
        main.cpp
        player.hpp
        menu_screen.hpp
        pause_screen.hpp
        game_screen.hpp)

add_executable(pong ${pong_src})

set_target_properties(pong PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(pong
        PUBLIC
            ${TORTUGA_LIB_INCLUDE}
            ${SFML_LIB_INCLUDE})

target_link_directories(pong
        PUBLIC
            ${SFML_LIB_PATH})

target_link_libraries(pong
        PUBLIC
            tortuga-core
            sfml-graphics
            sfml-window
            sfml-system)