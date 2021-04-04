cmake_minimum_required(VERSION 3.5)

project(LsbEncodingTestCase LANGUAGES CXX)

find_package(Qt5 COMPONENTS Test Core Gui REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(${PROJECT_NAME} tst_lsbencodingtestcase.cpp)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Test Qt5::Core Qt5::Gui Stg)

