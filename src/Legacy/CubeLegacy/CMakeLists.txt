# Cube/CMakeLists.txt

add_library(CubeLegacy STATIC CubeLegacy.cpp)

target_include_directories(CubeLegacy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CubeLegacy PRIVATE)