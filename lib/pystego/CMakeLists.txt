cmake_minimum_required(VERSION 3.12)

project(PyStg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

add_subdirectory("${PROJECT_SOURCE_DIR}/tests")

find_package(Python3 COMPONENTS Development Interpreter REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)
find_program(VIRTUALENV virtualenv REQUIRED)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)

include_directories(
    ${Stg_SOURCE_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Python3_INCLUDE_DIRS})

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE MODULE_NAME=${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES} Stg Boost::python)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

get_target_property(Stg_LINKED_LIBRARIES Stg LINK_LIBRARIES)
list(FILTER Stg_LINKED_LIBRARIES INCLUDE REGEX "Qt*")
list(APPEND Stg_LINKED_LIBRARIES Stg)
list(JOIN Stg_LINKED_LIBRARIES ";" LINKED_LIBRARIES)

set(SETUP_PY "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(EXTENSION_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/build")

file(COPY ${PROJECT_SOURCES} DESTINATION ${PROJECT_BINARY_DIR})
configure_file("${PROJECT_SOURCE_DIR}/setup.in.py" ${SETUP_PY})

set(VENV_DIR ${PROJECT_SOURCE_DIR}/venv)

add_custom_command(OUTPUT ${VENV_DIR}
        COMMAND ${Python3_EXECUTABLE} -m venv ${VENV_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${PROJECT_NAME} ${SETUP_PY}
        COMMENT "Setup virtual environment")

add_custom_command(OUTPUT ${EXTENSION_BINARY_DIR}
        COMMAND ${VENV_DIR}/bin/pip3 install .
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${PROJECT_NAME} ${SETUP_PY} ${VENV_DIR}
        COMMENT "Start build ${PROJECT_NAME} extension")

add_custom_target(${PROJECT_NAME}_EXTENSION ALL
        DEPENDS ${EXTENSION_BINARY_DIR}
        COMMENT "Successfully build ${PROJECT_NAME} extension")
