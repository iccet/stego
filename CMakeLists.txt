cmake_minimum_required(VERSION 3.16)
project(stego)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")

add_subdirectory(${SOURCE_DIR})
add_subdirectory(${TESTS_DIR})
