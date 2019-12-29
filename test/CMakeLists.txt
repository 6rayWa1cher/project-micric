cmake_minimum_required(VERSION 3.9.2)
project(project-micric)

add_executable(AllTests lexemtypetests.cpp tokentests.cpp scannertests.cpp)
target_link_libraries(AllTests gtest_main)
target_link_libraries(AllTests micric-lib)
add_test(NAME AllTests COMMAND AllTests)