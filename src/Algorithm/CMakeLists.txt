# Algorithm/CMakeLists.txt

add_library(Algorithm STATIC IDAStar.cpp)

target_include_directories(Algorithm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Algorithm
        PRIVATE
        Cube
        PatternDatabase
        Tables
)