cmake_minimum_required(VERSION 3.16)
project(project-micric)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(AllTests lexemtypetests.cpp tokentests.cpp scannertests.cpp)
target_link_libraries(AllTests gtest gtest_main)
target_link_libraries(AllTests micric-lib)
add_test(NAME AllTests COMMAND AllTests)
