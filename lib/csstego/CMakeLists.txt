cmake_minimum_required(VERSION 3.15)

project(CsStg)

include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)

include_directories(${PROJECT_BINARY_DIR})

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} Stg)

generate_export_header(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})
