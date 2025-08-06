cmake_minimum_required(VERSION 3.28.1)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Cube)
add_subdirectory(Algorithm)
add_subdirectory(PatternDatabase)
add_subdirectory(Tables)

enable_testing()
add_subdirectory(Tests)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Algorithm
)