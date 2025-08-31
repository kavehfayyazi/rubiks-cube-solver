#include "catch.hpp"

#include "pdb_handler.h"
#include <filesystem>
#include <string>
#include <cstdint>



#include <iostream>

namespace fs = std::filesystem;

static void checkPDBFile(const std::string& filename) {
    PdbHandler pdb = PdbHandler(filename);
    pdb.load();
    uint64_t bytes = pdb.getBytes();
    REQUIRE(bytes > 0);

    // Ensure all PDB nibbles are not 0x0F (default, unreached)
    for (size_t idx = 0; idx < bytes * 2; ++idx) {
        if (pdb.getPDBVal(idx) >= uint8_t(0x0F)) std::cout << idx << '\n';
        REQUIRE(pdb.getPDBVal(idx) < 0x0F);
    }
}

TEST_CASE("corner.pdb has all depths < 15") {
    checkPDBFile(PDB_CORNER_FILENAME);
}

TEST_CASE("edge_start.pdb has all depths < 15") {
    checkPDBFile(PDB_EDGE_FIRST_FILENAME);
}

TEST_CASE("edge_end.pdb has all depths < 15") {
    checkPDBFile(PDB_EDGE_SECOND_FILENAME);
}