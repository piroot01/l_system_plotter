include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "ConfigReader/*.cpp" "LibHaruFacade/*.cpp" "LSystemCreator/*.cpp" "LSystemInterpreter/*.cpp" "Utils/*.cpp")

add_library(LSystemPlotter ${SOURCES})
target_link_libraries(${PROJECT_NAME} hpdf)
