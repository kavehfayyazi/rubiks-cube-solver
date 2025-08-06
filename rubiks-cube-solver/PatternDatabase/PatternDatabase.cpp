//
//  PatternDatabase.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#include "PatternDatabase.h"
//#include "PDBFileHandler.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <thread>

void PatternDatabase::checkEdges(PieceType pieceType, const std::optional<std::array<unsigned char, 6>>& edgesArr) const {
    if (pieceType == PieceType::Edge && !edgesArr)
        throw std::invalid_argument("edgesArr required for edges.");
}

bool PatternDatabase::isHighNibble(uint64_t idx) const {
    return idx % 2;
}

uint64_t PatternDatabase::getPDBVal(std::vector<uint8_t>& pdb, uint64_t idx) const {
    if (isHighNibble(idx)) {
        return ((pdb[idx/2] & 0xF0) >> 4) & 0xF;
    } else {
        return pdb[idx/2] & 0x0F;
    }
}

void PatternDatabase::setPDBVal(std::vector<uint8_t>& pdb, uint64_t idx, unsigned char val) {
    if (isHighNibble(idx)) {
        pdb[idx/2] = (pdb[idx/2] & 0x0F) | (val << 4);
    } else {
        pdb[idx/2] = (pdb[idx/2] & 0xF0) | (val);
    }
}

uint64_t PatternDatabase::encodePermutationIndex(PieceType pieceType, const Cube& cube, const std::optional<std::array<unsigned char, 6>>& edgesArr) const {
    checkEdges(pieceType, edgesArr);
    const unsigned char len = (pieceType == PieceType::Corner) ? 8 : edgesArr->size();
    const uint64_t state = (pieceType == PieceType::Corner) ? cube.getCornerState() : cube.getEdgeState();
    uint64_t perm_index = 0;
    for (unsigned char i = 1; i < len; i++) {
        unsigned char num_larger = 0;
        unsigned char right = (pieceType == PieceType::Corner)
        ? cube.getState(pieceType, PiecePart::Position, state, i)
        : cube.getState(pieceType, PiecePart::Position, state, (*edgesArr)[i]);
        for (unsigned char j = 0; j < i; j++) {
            unsigned char left = (pieceType == PieceType::Corner)
            ? cube.getState(pieceType, PiecePart::Position, state, j)
            : cube.getState(pieceType, PiecePart::Position, state, (*edgesArr)[j]);
            if (left > right) num_larger++;
        }
        perm_index += num_larger * FACTORIAL[i];
    }
    return perm_index;
}

uint64_t PatternDatabase::oriBaseEncoding(PieceType pieceType, const Cube& cube, const std::optional<std::array<unsigned char, 6>>& edgesArr) const {
    checkEdges(pieceType, edgesArr);
    unsigned char base = 0, len = 0;
    uint64_t state = 0;
    if(pieceType == PieceType::Corner) {
        base = 3;
        len = 8 - 1; // -1 due to ability to track one less corner
        state = cube.getCornerState();
    } else {
        base = 2;
        len = edgesArr->size();
        state = cube.getEdgeState();
    }
    uint64_t val = 0;
    for(unsigned char i = 0; i < len; i++) {
        val = (pieceType == PieceType::Corner)
        ? val * base + cube.getState(pieceType, PiecePart::Orientation, state, i)
        : val * base + cube.getState(pieceType, PiecePart::Orientation, state, (*edgesArr)[i]);
    }
    return val;
}

uint64_t PatternDatabase::encodeState(PieceType pieceType, const Cube& cube, const std::optional<std::array<unsigned char, 6>>& edgesArr) const {
    uint64_t numTotalOrientations = (pieceType==PieceType::Corner) ? NUM_CORNER_ORIENTATIONS : NUM_EDGE_ORIENTATIONS;
    return encodePermutationIndex(pieceType, cube, edgesArr) * numTotalOrientations + oriBaseEncoding(pieceType, cube, edgesArr);
}

void PatternDatabase::generatePDB(PieceType pieceType, std::vector<uint8_t>& pdb, unsigned char maxDepth, const std::optional<std::array<unsigned char, 6>>& edgesArr) {
    Cube solved = Cube();
    
    std::queue<std::pair<Cube, unsigned char>> q;
    q.push({solved, 0});
    
    while(!q.empty()) {
        auto [currentCube, currentDepth] = q.front();
        q.pop();
        
        uint64_t idx = encodeState(pieceType, currentCube, edgesArr);
        // Progress check.
        visited++;
        if (visited % 1000000 == 0) std::cout << visited << " states visited...\n";
        
        if(getPDBVal(pdb, idx) == 0xF) {
            setPDBVal(pdb, idx, currentDepth);
            if(maxDepth > 0 && currentDepth < maxDepth) {
                for(auto& it: STRING_TO_MOVE) {
                    Cube changedCube = currentCube.move(it.first);
                    q.push({changedCube, currentDepth + 1});
                }
            }
        }
    }
}

void PatternDatabase::saveToFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::fstream file;

    file.open("sample.txt", std::ios::out | std::ios::binary | std::ios::trunc);
    if(file.is_open()){
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
    else {
        std::cerr << filename << " could not be opened." << std::endl;
    }
}

void PatternDatabase::mainPDB() {
    // No need to add one since CORNER_TOTAL and EDGE_TOTAL are even.
    std::vector<uint8_t> cornerPDB(     CORNER_TOTAL/2, 0xFF);
    std::vector<uint8_t> startEdgePDB(  EDGE_TOTAL/2  , 0xFF);
    std::vector<uint8_t> endEdgePDB(    EDGE_TOTAL/2  , 0xFF);
    std::thread t1([&]() {
        generatePDB(PieceType::Corner, cornerPDB, 15);
    });
    std::thread t2([&]() {
        generatePDB(PieceType::Edge, startEdgePDB, 15, std::array<unsigned char,6>{0,1,2,3,4,5});
    });
    std::thread t3([&]() {
        generatePDB(PieceType::Edge, endEdgePDB, 15, std::array<unsigned char,6>{6,7,8,9,10,11});
    });
    t1.join();
    t2.join();
    t3.join();
    saveToFile("corner.pdb",    cornerPDB);
    saveToFile("edge_start.pdb", startEdgePDB);
    saveToFile("edge_end.pdb",   endEdgePDB);
}