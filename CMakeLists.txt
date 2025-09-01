cmake_minimum_required(VERSION 3.28.0)
project(AlgoPractice CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
include(CTest)
# generates build outputs to build/bin instead of src
add_subdirectory(src bin)
add_subdirectory(test)