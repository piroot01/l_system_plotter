include_directories(${CMAKE_SOURCE_DIR}/include ${HPDF_INCLUDE_DIRS})

add_executable(HpdfExample main.cpp)

target_link_libraries(HpdfExample LSystemPlotter ${HPDF_LIBRARIES})

