cmake_minimum_required(VERSION 3.15)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(TORTUGA_MOD_COLLISION_LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(TORTUGA_MOD_COLLISION_HEADER
        include/tortuga/math/math.hpp)

set(TORTUGA_MOD_COLLISION_SOURCE
        src/math/math.cpp)

add_library(tortuga-mod-collision 
        ${TORTUGA_MOD_COLLISION_HEADER} 
        ${TORTUGA_MOD_COLLISION_SOURCE})

set_target_properties(tortuga-mod-collision PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(tortuga-mod-collision
        PUBLIC
            ${TORTUGA_MOD_COLLISION_LIB_INCLUDE})


# test
#enable_testing()
#include(GoogleTest)
#add_executable(tortuga_MOD_COLLISION_ut
#        test/math.t.cpp
#        test/matrix.t.cpp
#        test/hash.t.cpp
#        test/main.cpp)
#target_link_libraries(tortuga_MOD_COLLISION_ut PRIVATE gtest)
#gtest_add_tests(TARGET tortuga_MOD_COLLISION_ut)