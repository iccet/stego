cmake_minimum_required(VERSION 3.16)
project(Stego)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
set(TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include_directories(${LIB_DIR})

add_subdirectory(${SOURCE_DIR})
add_subdirectory(${LIB_DIR})
add_subdirectory(${TESTS_DIR})
