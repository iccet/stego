cmake_minimum_required(VERSION 3.5)

project(CrossIteratorTests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GENERIC_TEST_CASE "${PROJECT_SOURCE_DIR}/generic")
set(MATRIX_TEST_CASE "${PROJECT_SOURCE_DIR}/matrix")

enable_testing()

add_subdirectory(${GENERIC_TEST_CASE})
add_subdirectory(${MATRIX_TEST_CASE})

