# PatternDatabase/CMakeLists.txt

add_library(PatternDatabase STATIC PatternDatabase.cpp)

target_include_directories(PatternDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PatternDatabase
        PUBLIC
        Tables
        Cube
)

target_compile_definitions(PatternDatabase
        PUBLIC
        PDB_DIR=\"${CMAKE_SOURCE_DIR}/src/PatternDatabase/PDBs\"
)