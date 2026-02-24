cmake_minimum_required(VERSION 3.31)
project(2DGraphicsLib LANGUAGES CXX)

file(GLOB_RECURSE 2DGraphicsLib_Sources "./*.cpp")

add_library(2DGraphicsLib STATIC
        ${2DGraphicsLib_Sources}
)

target_include_directories(2DGraphicsLib PUBLIC
        "."
)

target_link_libraries(2DGraphicsLib PRIVATE
        GLCoreLib
        StylesLib
)