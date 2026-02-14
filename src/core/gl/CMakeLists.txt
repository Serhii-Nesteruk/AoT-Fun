cmake_minimum_required(VERSION 3.31)
project(GLCoreLib LANGUAGES CXX)

file(GLOB_RECURSE GLCoreLib_Sources "./*.cpp")

set(GLAD_SRC "${PROJECT_ROOT_DIR}/dependencies/glad/src")
set(GLAD_INCLUDE "${PROJECT_ROOT_DIR}/dependencies/glad/include/")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)

find_package(glm CONFIG REQUIRED)

add_library(GLCoreLib STATIC
    "${GLAD_SRC}/glad.c"
    ${GLCoreLib_Sources}
)

target_include_directories(GLCoreLib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${GLAD_INCLUDE}"
)

target_link_libraries(GLCoreLib PUBLIC
        glm::glm
)
target_compile_definitions(GLCoreLib PUBLIC GLM_FORCE_RADIANS)

target_link_libraries(GLCoreLib PRIVATE
        PkgConfig::GLFW
        StylesLib
)