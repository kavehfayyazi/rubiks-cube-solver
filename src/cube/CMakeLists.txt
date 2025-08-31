add_library(cube STATIC cube.cpp move.cpp cube_constants.cpp encode.cpp)

target_include_directories(cube PUBLIC ${CMAKE_SOURCE_DIR}/include/cube)