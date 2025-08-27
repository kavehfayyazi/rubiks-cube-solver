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
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

class PDBFileHandler {
public:
    static fs::path getFilePath(const std::string& filename) {
        std::string cwd(PDB_DIR);
        fs::path filePath = cwd + "/" + filename;
        return filePath;
    }

    PDBFileHandler(const std::string& filename) {
        fs::path filePath = getFilePath(filename);
        file.open(filePath, std::ios::in | std::ios::binary);
        if(!file.is_open()) throw std::runtime_error("Cannot open file: " + filePath.string());

        file.seekg(0, std::ios::end);
        long fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(fileSize);
        file.read(buffer.data(), fileSize);
        if(!file) throw std::runtime_error("Cannot read file: " + filename);

        pdb.clear();
        pdb.reserve(buffer.size());
        std::transform(
                buffer.begin(), buffer.end(),
                std::back_inserter(pdb),
                [](char c){ return static_cast<uint8_t>(c); }
        );
    }

    inline uint8_t search(size_t idx) const {
        if (idx & 1) return (pdb[idx / 2] >> 4) & 0xF;
        else return pdb[idx / 2] & 0xF;
    }

private:
    std::ifstream file;
    std::vector<uint8_t> pdb;
};

#endif //RUBIKS_CUBE_SOLVER_PDBFILEHANDLER_H
