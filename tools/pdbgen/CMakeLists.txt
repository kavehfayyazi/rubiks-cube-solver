add_library(pdbgen STATIC pdbgen_run.cpp)

target_include_directories(pdbgen PUBLIC ${CMAKE_SOURCE_DIR}/tools/pdbgen)

target_link_libraries(pdbgen PUBLIC ida_star)
