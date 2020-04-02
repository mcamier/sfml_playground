cmake_minimum_required(VERSION 3.15)

project(tortuga
        VERSION 0.1
        LANGUAGES C CXX)

# SFML library build
#add_subdirectory(./libs/SFML-2.5.1-sources)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "./libs/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML REQUIRED COMPONENTS main graphics window system audio network)

message("ADD DEFINITION 'RUNNING_LINUX'")
add_definitions(-DRUNNING_LINUX=1)
message("ADD DEFINITION 'PROFILING_ENABLED'")
add_definitions(-DPROFILING_ENABLED=1)
message("ADD DEFINITION 'LOGGING_ENABLED'")
add_definitions(-DLOGGING_ENABLED=1)

#message(ADD DEFINTION "RUNNING_WINDOWS")
#add_definitions(-DRUNNING_WINDOWS=1)

add_subdirectory(libs/googletest)

add_subdirectory(tortuga-core)
add_subdirectory(experiments)
add_subdirectory(resource_bundler)

add_subdirectory(pong)
add_subdirectory(ong)
