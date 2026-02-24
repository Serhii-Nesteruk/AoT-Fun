cmake_minimum_required(VERSION 3.31)
project(StylesLib LANGUAGES CXX)

file(GLOB_RECURSE StylesLib_Sources "./*.cpp")

add_library(StylesLib INTERFACE)