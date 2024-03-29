cmake_minimum_required(VERSION 3.15)

project(CsStg)

include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)

include_directories(
    ${Stg_SOURCE_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR})

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Stg
    Qt${QT_VERSION_MAJOR}::Core Qt5::Gui)

generate_export_header(${PROJECT_NAME})

get_target_property(CsStg_LINKED_LIBRARIES ${PROJECT_NAME} LINK_LIBRARIES)
list(APPEND CsStg_LINKED_LIBRARIES ${PROJECT_NAME})

set(DEPS_FILE ${PROJECT_BINARY_DIR}/deps.txt)

list(JOIN CsStg_LINKED_LIBRARIES ">\n$<TARGET_FILE:" CsStg_LINKED_LIBRARIES)
set(CsStg_LINKED_LIBRARIES "$<TARGET_FILE:${CsStg_LINKED_LIBRARIES}>")

file(GENERATE OUTPUT ${DEPS_FILE}
    CONTENT $<GENEX_EVAL:${CsStg_LINKED_LIBRARIES}>)
