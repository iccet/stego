cmake_minimum_required(VERSION 3.12)

project(Tests)

enable_testing()

add_test(NAME Python${PROJECT_NAME}
    COMMAND ${Python3_EXECUTABLE} -m unittest discover -v -s ${CMAKE_CURRENT_SOURCE_DIR} -p "*_test_case.py"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
