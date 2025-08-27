#include "catch.hpp"

#include "PDBFileHandler.h"
#include <filesystem>
#include <string>
#include <cstdint>

namespace fs = std::filesystem;

static void checkPDBFile(const std::string& filename) {
    PDBFileHandler pdb = PDBFileHandler(filename);
    pdb.load();
    uint64_t bytes = pdb.getBytes();
    REQUIRE(bytes > 0);

    // Ensure all PDB nibbles are not 0x0F (default, unreached)
    for (size_t idx = 0; idx < bytes * 2; ++idx) REQUIRE(pdb.getPDBVal(idx) < 0x0F);
}

TEST_CASE("corner.pdb has all depths < 15") {
    checkPDBFile("corner.pdb");
}

TEST_CASE("edge_start.pdb has all depths < 15") {
    checkPDBFile("edgeFirst.pdb");
}

TEST_CASE("edge_end.pdb has all depths < 15") {
    checkPDBFile("edgeSecond.pdb");
}