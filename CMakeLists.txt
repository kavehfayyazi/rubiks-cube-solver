cmake_minimum_required(VERSION 3.28.1)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Changeable Pattern Database Variables
set(PDB_DIR               "${CMAKE_SOURCE_DIR}/pdb" CACHE PATH   "Default directory for PDB files at runtime")
set(PDB_CORNER_FILE       "corner.pdb"              CACHE STRING "Corner PDB filename")
set(PDB_EDGE_FIRST_FILE   "edge_first.pdb"          CACHE STRING "Edge-first PDB filename")
set(PDB_EDGE_SECOND_FILE  "edge_second.pdb"         CACHE STRING "Edge-second PDB filename")

add_library(pdb_config INTERFACE)
target_compile_definitions(pdb_config INTERFACE
        PDB_DIR="${PDB_DIR}"
        PDB_CORNER_FILENAME="${PDB_CORNER_FILE}"
        PDB_EDGE_FIRST_FILENAME="${PDB_EDGE_FIRST_FILE}"
        PDB_EDGE_SECOND_FILENAME="${PDB_EDGE_SECOND_FILE}"
)

add_subdirectory(src/cube)
add_subdirectory(src/ida_star)
add_subdirectory(tools/pdbgen)
add_subdirectory(tools/maxdepths)
add_subdirectory(tools/cli)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

option(BUILD_TESTS "Build tests" ON) # Set to ON for testing