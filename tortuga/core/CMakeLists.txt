cmake_minimum_required(VERSION 3.15)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(TORTUGA_CORE_LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(TORTUGA_CORE_HEADER
        include/tortuga/math/math.hpp
        include/tortuga/math/plane.hpp
        include/tortuga/math/rect.hpp
        include/tortuga/math/vector.hpp
        include/tortuga/math/matrix.hpp
        include/tortuga/core.hpp
        include/tortuga/clock.hpp
        include/tortuga/hash.hpp
        include/tortuga/memory.hpp
        include/tortuga/service.hpp
        include/tortuga/configuration.hpp
        include/tortuga/log_utils.hpp
        include/tortuga/stringId.hpp
        include/tortuga/types.hpp)

set(TORTUGA_CORE_SOURCE
        src/math/math.cpp
        src/clock.cpp
        src/core.cpp
        src/stringId.cpp
        src/memory.cpp
        src/configuration.cpp
        )

add_library(tortuga-core 
        ${TORTUGA_CORE_HEADER} 
        ${TORTUGA_CORE_SOURCE})

set_target_properties(tortuga-core PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(tortuga-core
        PUBLIC
            ${TORTUGA_CORE_LIB_INCLUDE})


# test
enable_testing()
include(GoogleTest)
add_executable(tortuga_core_ut
        test/vector.t.cpp
        test/matrix.t.cpp
        test/hash.t.cpp
        test/main.cpp)
target_link_libraries(tortuga_core_ut PRIVATE gtest)
gtest_add_tests(TARGET tortuga_core_ut)