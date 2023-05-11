cmake_minimum_required(VERSION 3.0)
project(LSystemInterpreter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES "src/main.cpp" "src/LSystemInterpreter/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

