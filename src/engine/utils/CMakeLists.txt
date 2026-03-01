cmake_minimum_required(VERSION 3.31)
project(CoreUtilsLib LANGUAGES CXX)

file(GLOB_RECURSE CoreUtilsLib_Sources "./*.cpp")

add_library(CoreUtilsLib STATIC
        ${CoreUtilsLib_Sources}
)

target_include_directories(CoreUtilsLib PUBLIC
        "."
)

target_link_libraries(CoreUtilsLib PRIVATE
        GLCoreLib
)