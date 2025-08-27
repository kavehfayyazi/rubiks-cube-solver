//
// Created by Kaveh Fayyazi on 8/5/25.
//

#ifndef RUBIKS_CUBE_SOLVER_PDBFILEHANDLER_H
#define RUBIKS_CUBE_SOLVER_PDBFILEHANDLER_H

#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

class PDBFileHandler {
public:
    fs::path getFilePath(const std::string fn);

    PDBFileHandler(const std::string& fileName);

    void load();
    void save(const std::vector<uint8_t>& data);
    uint8_t getPDBVal(uint64_t idx) const;
    uint64_t getBytes() const;

    // static array helpers
    static bool isHighNibble(uint64_t idx);
    static bool notReached(std::vector<uint8_t>& data, uint64_t idx); // all nibbles are defaulted to 0x0F
    static uint8_t getVal(std::vector<uint8_t>& data, uint64_t idx);
    static void setVal(std::vector<uint8_t>& data, uint64_t idx, uint8_t val);

private:
    std::string fileName;
    fs::path filePath;
    std::vector<uint8_t> pdb;
};

#endif //RUBIKS_CUBE_SOLVER_PDBFILEHANDLER_H
