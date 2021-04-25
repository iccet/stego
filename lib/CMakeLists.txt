cmake_minimum_required(VERSION 3.16)
project(Libs)

set(STEGO_DIR "${PROJECT_SOURCE_DIR}/stego")
set(PYSTEGO_DIR "${PROJECT_SOURCE_DIR}/pystego")

add_subdirectory(${STEGO_DIR})
add_subdirectory(${PYSTEGO_DIR} EXCLUDE_FROM_ALL)
