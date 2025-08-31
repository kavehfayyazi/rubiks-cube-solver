add_executable(cli ${CMAKE_SOURCE_DIR}/app/cli.cpp)

target_link_libraries(cli PRIVATE cube solver pdbgen maxdepths pdb_config)