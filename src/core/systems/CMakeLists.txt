cmake_minimum_required(VERSION 3.31)
project(SystemsLib LANGUAGES CXX)

file(GLOB_RECURSE SystemsLib_Sources "./*.cpp")

add_library(SystemsLib STATIC
    "${SystemsLib_Sources}"
)

target_include_directories(SystemsLib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(SystemsLib PRIVATE
    GLCoreLib
)