cmake_minimum_required(VERSION 3.31)
project(AoT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src/core/gl)
add_subdirectory(src/core/style)

add_executable(AoT
        src/main.cpp
)

target_link_libraries(AoT PRIVATE
        GLCoreLib
)