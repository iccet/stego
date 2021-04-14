cmake_minimum_required(VERSION 3.5)

project(KutterTests LANGUAGES CXX)

include(subdirlist)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SUBDIRLIST(SUBDIRS ${PROJECT_SOURCE_DIR})

foreach(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
endforeach()
