add_library(solver STATIC solve.cpp)

target_include_directories(solver PUBLIC ${CMAKE_SOURCE_DIR}/include/app)

target_link_libraries(solver PRIVATE cube ida_star)