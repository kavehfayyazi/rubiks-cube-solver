# Cube/CMakeLists.txt

add_library(Cube STATIC Cube.cpp)

target_include_directories(Cube PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Cube
        PRIVATE
        Tables
)