# Tables/CMakeLists.txt

add_library(Tables STATIC moveTables.cpp)

target_include_directories(Tables PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})