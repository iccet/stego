cmake_minimum_required(VERSION 3.14)

project(LibStego LANGUAGES CXX)

string(TOLOWER ${PROJECT_NAME} LIB_NAME)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)
find_package(Boost COMPONENTS program_options log log_setup REQUIRED)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

add_library(${LIB_NAME} STATIC ${PROJECT_SOURCES})

target_link_libraries(${LIB_NAME}
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt5::Gui
        Boost::program_options PUBLIC Boost::log Boost::log_setup)

target_link_libraries(${LIB_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt5::Gui)

target_compile_definitions(${LIB_NAME} PRIVATE LIBSTEGO_LIBRARY)
