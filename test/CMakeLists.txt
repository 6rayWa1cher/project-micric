cmake_minimum_required(VERSION 3.9.2)
project(project-micric)

add_executable(AllTests lexemtypetests.cpp tokentests.cpp scannertests.cpp ${SRC_FILES} lib/TestUtils.cpp lib/TestUtils.h)
target_link_libraries(AllTests gtest_main)
add_test(NAME AllTests COMMAND AllTests)