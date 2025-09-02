add_executable(cli ${CMAKE_SOURCE_DIR}/tools/cli/cli.cpp)

target_link_libraries(cli PRIVATE pdbgen maxdepths pdb_config)