cmake_minimum_required(VERSION 3.9.2)
project(mini_cpp_compiler)

add_executable(AllTests basetest.cpp)
add_test(NAME AllTests COMMAND AllTests)