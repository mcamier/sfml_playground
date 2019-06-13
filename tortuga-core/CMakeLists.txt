cmake_minimum_required(VERSION 3.14)

# Enable c++17 capatibility
set(CMAKE_CXX_STANDARD 17)

set(TORTUGA_LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/inc PARENT_SCOPE)
set(TORTUGA_CORE_HEADER
        inc/TE/math/math.hpp
        inc/TE/math/plane.hpp
        inc/TE/math/vec2.hpp
        inc/TE/math/vec3.hpp
        inc/TE/resource/resource_info.hpp
        inc/TE/resource/resource_service.hpp
        inc/TE/screen/screen.hpp
        inc/TE/screen/screen_service.hpp
)
set(TORTUGA_CORE_SOURCE
        src/math/math.cpp
        src/service_locator.cpp
        src/resource/resource_service.cpp
        src/message/message_service.cpp
        src/message/subscription.cpp
        src/message/message.cpp
        src/screen/screen.cpp
        src/screen/screen_service.cpp
)

add_library(tortuga-core 
        ${TORTUGA_CORE_HEADER} 
        ${TORTUGA_CORE_SOURCE})

set_target_properties(tortuga-core PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

target_include_directories(tortuga-core
        PUBLIC
            ${TORTUGA_LIB_INCLUDE}
            ${SFML_LIB_INCLUDE})

target_link_directories(tortuga-core
        PUBLIC
            ${SFML_LIB_PATH})

target_link_libraries(tortuga-core
        PUBLIC
            sfml-graphics
            sfml-window
            sfml-system
            sfml-audio)