cmake_minimum_required(VERSION 3.5)

project(FreedomTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_CASE "${PROJECT_SOURCE_DIR}/template")

add_subdirectory(${TEST_CASE})

