cmake_minimum_required(VERSION 3.14)

project(foobar
        VERSION 0.1
        LANGUAGES C CXX)

SET(SFML_LIB_PATH "C:\\Program\ Files\ (x86)\\SFML\\lib")
SET(SFML_LIB_INCLUDE "C:\\Program\ Files\ (x86)\\SFML\\include")

add_subdirectory(utils)
add_subdirectory(pong)