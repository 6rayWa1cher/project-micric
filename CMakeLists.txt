cmake_minimum_required(VERSION 3.16)
project(project-micric)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")

#Requires CMake 3.16+
include(FetchContent)

FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG release-1.8.1
)

FetchContent_MakeAvailable(googletest)


file(GLOB Micric_SRC_FILES
		${PROJECT_SOURCE_DIR}/src/core/*.cpp
		${PROJECT_SOURCE_DIR}/src/include/*.h
		${PROJECT_SOURCE_DIR}/src/lib/*.cpp
		${PROJECT_SOURCE_DIR}/src/lib/*.h)


enable_testing()
add_subdirectory(src)
add_subdirectory(test)