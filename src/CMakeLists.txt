add_subdirectory(Cube)
add_subdirectory(Algorithm)
add_subdirectory(PatternDatabase)
add_subdirectory(Tables)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Algorithm)