cmake_minimum_required(VERSION 3.9.2)
project(mini_cpp_compiler)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
include_directories(include)
add_subdirectory(src)
add_subdirectory(test)