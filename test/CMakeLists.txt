cmake_minimum_required(VERSION 3.15)
project(mini_cpp_compiler)

add_executable(AllTests basetest.cpp)
add_test(NAME AllTests COMMAND AllTests)