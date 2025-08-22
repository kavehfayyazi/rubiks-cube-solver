# Tests/CMakeLists.txt

add_executable(Tests cubeTests.cpp pdbTests.cpp main_tests.cpp)

target_include_directories(Tests PRIVATE ${CMAKE_SOURCE_DIR}/Tests/Include)

target_link_libraries(Tests
    PUBLIC
        Algorithm
        PatternDatabase
        Cube
        Tables
)

add_test(NAME AllUnitTests COMMAND Tests)