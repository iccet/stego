cmake_minimum_required(VERSION 3.5)

project(PyStg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

find_package(Python3 COMPONENTS Development Interpreter REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

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

set(SETUP_PY "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(DEPS "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py")
set(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}")

configure_file("${PROJECT_SOURCE_DIR}/setup.in.py" ${SETUP_PY})
file(COPY ${PROJECT_SOURCES} DESTINATION ${PROJECT_BINARY_DIR})

message(STATUS ${CMAKE_COMMAND})
add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${Python3_EXECUTABLE} ${SETUP_PY} build
    COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
    DEPENDS ${DEPS})

add_custom_target(target ALL DEPENDS ${OUTPUT})

install(CODE "execute_process(COMMAND ${Python3_EXECUTABLE} ${SETUP_PY} install)")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE MODULE_NAME=${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES} Stg)

get_target_property(OUT Stg LINK_LIBRARIES)
message(STATUS ${OUT})
list(FILTER ${OUT} INCLUDE REGEX "Qt5::")
message(STATUS ${output})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
