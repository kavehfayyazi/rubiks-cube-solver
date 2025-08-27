# PatternDatabase/CMakeLists.txt

add_library(PatternDatabaseLegacy STATIC PatternDatabase.cpp)

target_include_directories(PatternDatabaseLegacy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PatternDatabaseLegacy PUBLIC CubeLegacy)

target_compile_definitions(PatternDatabaseLegacy PUBLIC PDB_LEGACY_DIR=\"${CMAKE_SOURCE_DIR}/src/PatternDatabase/PDBs\")