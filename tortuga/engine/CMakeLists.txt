cmake_minimum_required(VERSION 3.15)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(TORTUGA_ENGINE_LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(TORTUGA_ENGINE_HEADER
        include/tortuga/Screen.hpp)

set(TORTUGA_ENGINE_SOURCE
        src/Screen.cpp
        )

add_library(tortuga-engine
        ${TORTUGA_ENGINE_HEADER}
        ${TORTUGA_ENGINE_SOURCE})

set_target_properties(tortuga-engine PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(tortuga-engine
        PUBLIC
            ${SFML_LIB_INCLUDE}
            ${TORTUGA_CORE_LIB_INCLUDE}
            ${TORTUGA_ENGINE_LIB_INCLUDE})

target_link_directories(tortuga-core
        PUBLIC
            ${SFML_LIB_PATH})

target_link_libraries(tortuga-core
        PUBLIC
            tortuga-core
            sfml-graphics
            sfml-window
            sfml-system
            sfml-audio)

# test
#enable_testing()
#include(GoogleTest)
#add_executable(unitTests test/test.cpp)
#target_link_libraries(unitTests PRIVATE gtest)
#gtest_add_tests(
#        TARGET unitTests
#)