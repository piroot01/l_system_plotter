cmake_minimum_required(VERSION 3.0)
project(LSystemPlotter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O1 -pthread")

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

include_directories(${INCLUDE_DIR})

file(GLOB SOURCES ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/Timer.cpp ${SOURCE_DIR}/HpdfApi.cpp ${SOURCE_DIR}/Colors.cpp ${SOURCE_DIR}/Time.cpp ${SOURCE_DIR}/LSystem.cpp ${SOURCE_DIR}/ConfigReader.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} hpdf)
