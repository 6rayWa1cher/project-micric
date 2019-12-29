cmake_minimum_required(VERSION 3.9.2)
project(project-micric)

add_executable(micric main.cpp ${Micric_SRC_FILES})
target_include_directories(micric PRIVATE include/ lib/)

add_library(micric-lib STATIC ${Micric_SRC_FILES})
target_include_directories(micric-lib PUBLIC include/)