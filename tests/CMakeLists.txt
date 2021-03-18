cmake_minimum_required(VERSION 3.5)

project(Tests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LSB_TEST_CASE "${PROJECT_SOURCE_DIR}/lsb")
set(TEMPLATE_TEST_CASE "${PROJECT_SOURCE_DIR}/template")

enable_testing()

add_subdirectory(${LSB_TEST_CASE})
add_subdirectory(${TEMPLATE_TEST_CASE})

