cmake_minimum_required(VERSION 3.14)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

add_executable(exp_matrix exp_matrix.cpp)

set_target_properties(exp_matrix PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(exp_matrix
        PUBLIC
            utils)

target_link_libraries(exp_matrix
        PUBLIC
            utils)