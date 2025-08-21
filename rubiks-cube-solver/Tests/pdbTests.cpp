#include "catch.hpp"

#include "PDBFileHandler.h"
#include <filesystem>
#include <string>
#include <cstdint>

namespace fs = std::filesystem;

static void checkPDBFile(const std::string& filename) {
    // Resolve full path the same way your code saves/opens PDBs
    fs::path path = PDBFileHandler::getFilePath(filename);
    const auto bytes = fs::file_size(path);
    REQUIRE(bytes > 0);

    // Two 4-bit depths per byte
    const size_t totalEntries = static_cast<size_t>(bytes) * 2;
    PDBFileHandler pdb(filename);

    for (size_t idx = 0; idx < totalEntries; ++idx) {
        const uint8_t depth = pdb.search(idx);
        // Depths must be in [0,14]; 15 (0xF) means "unvisited"
        INFO("filename=" << filename << " idx=" << idx << " depth=" << static_cast<int>(depth));
        REQUIRE((int)depth < 15);
    }
}

TEST_CASE("corner.pdb has all depths < 15") {
checkPDBFile("corner.pdb");
}

TEST_CASE("edge_start.pdb has all depths < 15") {
checkPDBFile("edge_start.pdb");
}

TEST_CASE("edge_end.pdb has all depths < 15") {
checkPDBFile("edge_end.pdb");
}