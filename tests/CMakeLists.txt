# Tests/CMakeLists.txt

add_executable(Tests cubeTests.cpp pdbTests.cpp main_tests.cpp)

target_include_directories(Tests PRIVATE ${CMAKE_SOURCE_DIR}/tests/include)

target_link_libraries(Tests PUBLIC cube ida_star solver pdb_config)

add_test(NAME AllUnitTests COMMAND Tests)