cmake_minimum_required(VERSION 3.14)

project(tortuga
        VERSION 0.1
        LANGUAGES C CXX)

SET(SFML_LIB_PATH "/usr/local/Cellar/sfml/2.5.1/lib")
SET(SFML_LIB_INCLUDE "/usr/local/Cellar/sfml/2.5.1/include")

add_subdirectory(tortuga-core)
add_subdirectory(experiments)
add_subdirectory(tools)

add_subdirectory(pong)
add_subdirectory(ong)