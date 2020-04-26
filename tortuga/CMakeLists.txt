cmake_minimum_required(VERSION 3.15)

project(tortuga
        VERSION 0.1
        LANGUAGES C CXX)

add_subdirectory(core)
#add_subdirectory(modules/ecs)
#add_subdirectory(modules/collision)
#add_subdirectory(modules/physic)
add_subdirectory(engine)
add_subdirectory(resource_bundler)