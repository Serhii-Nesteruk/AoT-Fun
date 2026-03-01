cmake_minimum_required(VERSION 3.31)
project(AoT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src/engine/core/gl)
add_subdirectory(src/engine/utils/)
add_subdirectory(src/engine/core/style)
add_subdirectory(src/engine/systems)
add_subdirectory(src/engine/2DGraphics)

add_executable(AoT
        src/main.cpp
        src/App.cpp
        src/GameTemplate2D.cpp
)

target_link_libraries(AoT PRIVATE
        GLCoreLib
        CoreUtilsLib
        SystemsLib
        2DGraphicsLib
)