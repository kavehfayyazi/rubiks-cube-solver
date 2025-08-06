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
    PDBFileHandler(const std::string& filename){
        std::string cwd(PDB_DIR);
        fs::path filePath = cwd + "/" + filename;
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

    uint8_t search(size_t idx) const {
        return pdb.at(idx);
    }
private:
    std::ifstream file;
    std::vector<uint8_t> pdb;
};

#endif //RUBIKS_CUBE_SOLVER_PDBFILEHANDLER_H
