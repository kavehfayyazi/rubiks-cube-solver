//
// Created by Kaveh Fayyazi on 8/26/25.
//


//
// Created by Kaveh Fayyazi on 8/5/25.
//

#include "PDBFileHandler.h"

namespace fs = std::filesystem;

fs::path PDBFileHandler::getFilePath(const std::string fn) { return fs::path(PDB_DIR) / fn; }

PDBFileHandler::PDBFileHandler(const std::string& fileName) : fileName(fileName), filePath(getFilePath(fileName)) {};

void PDBFileHandler::load() {
    std::ifstream in(filePath, std::ios::in | std::ios::binary);
    if(!in.is_open()) throw std::runtime_error("Cannot open file: " + filePath.string());

    // Get length of the data
    in.seekg(0, std::ios::end);
    auto size = in.tellg();
    if (size < 0) throw std::runtime_error("tellg() failed for: " + filePath.string());
    in.seekg(0, std::ios::beg);

    // Makes a buffer of adequate size
    std::vector<char> buffer(size);
    in.read(buffer.data(), size);
    if(!in) throw std::runtime_error("Cannot read file: " + fileName);

    pdb.resize(size);
    std::transform(
            buffer.begin(), buffer.end(), pdb.begin(),
            [](char c){ return static_cast<uint8_t>(c); }
    );
}

void PDBFileHandler::save(const std::vector<uint8_t>& data) {
    std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
    if(out.is_open()) out.write(reinterpret_cast<const char*>(data.data()), data.size());
    else std::cerr << fileName << " could not be opened." << std::endl;
}

uint8_t PDBFileHandler::getPDBVal(uint64_t idx) const {
    if (idx >= pdb.size() * 2ULL) throw std::out_of_range("PDB index out of range");
    const uint8_t byte = pdb[idx / 2];
    return (idx & 1) ? ((byte >> 4) & 0x0F) : (byte & 0x0F);
}

uint64_t PDBFileHandler::getBytes() const { return pdb.size(); }

// static array helpers
bool PDBFileHandler::isHighNibble(uint64_t idx) { return idx & 1; }

uint8_t PDBFileHandler::getVal(std::vector<uint8_t>& data, uint64_t idx) {
    if (idx >= data.size() * 2ULL) throw std::out_of_range("PDB index out of range");
    const uint8_t byte = data[idx / 2];
    return (idx & 1) ? ((byte >> 4) & 0x0F) : (byte & 0x0F);
}

// all nibbles are defaulted to 0x0F
bool PDBFileHandler::notReached(std::vector<uint8_t>& data, uint64_t idx) { return getVal(data, idx) == 0x0F; }

void PDBFileHandler::setVal(std::vector<uint8_t>& data, uint64_t idx, uint8_t val) {
    if (idx >= data.size() * 2ULL) throw std::out_of_range("PDB index out of range");
    val &= 0x0F;
    if (isHighNibble(idx)) {
        data[idx/2] = (data[idx/2] & 0x0F) | (val << 4);
    } else {
        data[idx/2] = (data[idx/2] & 0xF0) | (val);
    }
}
