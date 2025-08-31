add_library(maxdepths STATIC maxdepths_run.cpp)

target_include_directories(maxdepths PUBLIC ${CMAKE_SOURCE_DIR}/tools/maxdepths)

target_link_libraries(maxdepths PRIVATE cube)