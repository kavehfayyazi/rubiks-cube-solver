# Tests/CMakeLists.txt

add_executable(Tests mainTests.cpp)

target_link_libraries(Tests
    PRIVATE
        Algorithm
        PatternDatabase
        Cube
        Tables
)

add_test(NAME AllUnitTests COMMAND Tests)