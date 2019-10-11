cmake_minimum_required(VERSION 3.15)
project(mini_cpp_compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
enable_testing()