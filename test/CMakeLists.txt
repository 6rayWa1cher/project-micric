cmake_minimum_required(VERSION 3.9.2)
project(mini_cpp_compiler)

add_executable(AllTests basetest.cpp ../src/core/coolnumber.cpp ../src/include/coolnumber.h)
target_link_libraries(AllTests gtest_main)
add_test(NAME AllTests COMMAND AllTests)