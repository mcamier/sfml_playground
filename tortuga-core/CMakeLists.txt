cmake_minimum_required(VERSION 3.15)

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
        inc/TE/screen/Screen.hpp
        inc/TE/screen/ScreenService.hpp
        inc/TE/screen/ui/UIScreen.hpp
        inc/TE/screen/ui/element/UIElement.hpp
        inc/TE/core/IEventHandler.hpp
        inc/TE/core/IRenderable.hpp
        inc/TE/core/IUpdatable.hpp
        inc/TE/core/core.hpp
        inc/TE/GameApp.hpp
        inc/TE/memory.hpp
        inc/TE/logger.hpp
        inc/TE/profiler.hpp
        )

set(TORTUGA_CORE_SOURCE
        src/math/math.cpp
        src/resource/resource_service.cpp
        src/message/message_service.cpp
        src/message/subscription.cpp
        src/message/message.cpp
        src/screen/Screen.cpp
        src/screen/ScreenService.cpp
        src/screen/ui/UIScreen.cpp
        src/GameApp.cpp
        src/memory.cpp
        src/profiler.cpp
        src/logger.cpp
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