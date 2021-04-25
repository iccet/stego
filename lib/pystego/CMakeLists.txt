cmake_minimum_required(VERSION 3.12)

project(PyStg VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)
add_subdirectory(${TESTS_DIR})

find_package(Python3 COMPONENTS Development Interpreter REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)
find_package(Boost COMPONENTS python program_options log log_setup REQUIRED)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)
file(GLOB PYTHON_FILES ${PROJECT_SOURCE_DIR}/*.py)

include_directories(
    ${Stg_SOURCE_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Python3_INCLUDE_DIRS})

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE
        PROJECT_NAME="${PROJECT_NAME}"
        PROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES} Stg Boost::python)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

get_target_property(Stg_LINKED_LIBRARIES Stg LINK_LIBRARIES)
list(APPEND Stg_LINKED_LIBRARIES Boost::python)

foreach(lib ${Stg_LINKED_LIBRARIES})
    get_target_property(lib_location ${lib} LOCATION)
    get_filename_component(lib_name ${lib_location} NAME_WE)
    string(REPLACE "lib" "" lib_name ${lib_name})
    list(POP_FRONT Stg_LINKED_LIBRARIES unused)
    list(APPEND Stg_LINKED_LIBRARIES ${lib_name})
endforeach()

list(APPEND Stg_LINKED_LIBRARIES Stg)

list(JOIN Stg_LINKED_LIBRARIES ";" LINKED_LIBRARIES)

set(SETUP_PY "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(EXTENSION_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/build")
set(PACKAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}/dist")
set(PACKAGE_FILES "${PROJECT_SOURCE_DIR}/README.md")

file(COPY ${PROJECT_SOURCES} ${PACKAGE_FILES} DESTINATION ${PROJECT_BINARY_DIR})
configure_file("${PROJECT_SOURCE_DIR}/setup.in.py" ${SETUP_PY})

set(VENV_DIR ${PROJECT_SOURCE_DIR}/venv)
set(PYTHON_EXECUTABLE ${VENV_DIR}/bin/python3)
set(PIP_EXECUTABLE ${VENV_DIR}/bin/pip3)

add_custom_command(OUTPUT ${VENV_DIR}
        COMMAND ${Python3_EXECUTABLE} -m venv ${VENV_DIR}
        COMMAND ${PYTHON_EXECUTABLE} -m pip install --upgrade pip
        COMMAND ${PIP_EXECUTABLE} install wheel
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${PROJECT_NAME} ${SETUP_PY}
        COMMENT "Setup virtual environment")

add_custom_command(OUTPUT ${EXTENSION_BINARY_DIR}
        COMMAND ${PIP_EXECUTABLE} -v install -vU --no-cache-dir .
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${PROJECT_NAME} ${SETUP_PY} ${VENV_DIR}
        COMMENT "Start build ${PROJECT_NAME} extension")

add_custom_target(${PROJECT_NAME}Extension ALL
        DEPENDS ${EXTENSION_BINARY_DIR}
        COMMENT "Successfully build ${PROJECT_NAME} extension")

add_custom_command(OUTPUT ${PACKAGE_DIR}
        COMMAND ${PIP_EXECUTABLE} install --upgrade build
        COMMAND ${PYTHON_EXECUTABLE} -m build
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${PROJECT_NAME} ${SETUP_PY} ${VENV_DIR}
        COMMENT "Start build ${PROJECT_NAME} package")

add_custom_target(Build${PROJECT_NAME}Package ALL
        DEPENDS ${PACKAGE_DIR}
        COMMENT "Successfully build ${PROJECT_NAME} package")

add_custom_target(Upload${PROJECT_NAME}Package ALL
        COMMAND ${PYTHON_EXECUTABLE} -m pip install --upgrade twine
        COMMAND ${PYTHON_EXECUTABLE} -m twine upload -r testpypi *
        DEPENDS ${PACKAGE_DIR}
        WORKING_DIRECTORY ${PACKAGE_DIR}
        COMMENT "Successfully uploaded ${PROJECT_NAME} package")

enable_testing()
set(TESTS_NAME ${PROJECT_NAME}Tests)

if(${Python3_VERSION} VERSION_GREATER_EQUAL "3.9.0")
    add_custom_target(${TESTS_NAME} ALL
        DEPENDS ${PROJECT_NAME}Extension
        COMMAND ${PYTHON_EXECUTABLE} -m unittest discover -v -s ${TESTS_DIR} -p "*_test_case.py")

    add_test(${TESTS_NAME} ${TESTS_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
