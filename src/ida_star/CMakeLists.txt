add_library(ida_star STATIC ida_star.cpp pdb_handler.cpp)

target_include_directories(ida_star PUBLIC ${CMAKE_SOURCE_DIR}/include/ida_star)

target_link_libraries(ida_star PUBLIC cube pdb_config)