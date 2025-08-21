//
//  PatternDatabase.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#include "PatternDatabase.h"
#include "PDBFileHandler.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <thread>
#include <unordered_set>

namespace fs = std::filesystem;

unsigned char PatternDatabase::getEdgeIdx(unsigned char idx, bool isFirstEdgeGroup) const {
    if(idx >= NUM_EDGES_IN_GROUP) throw std::invalid_argument("Edge index out of range.");
    if(isFirstEdgeGroup) return edgesFirstHalf[idx];
    return edgesSecondHalf[idx];
}

bool PatternDatabase::isHighNibble(uint64_t idx) { return idx & 1; }

uint64_t PatternDatabase::getPDBVal(std::vector<uint8_t>& pdb, uint64_t idx) {
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

constexpr uint64_t PatternDatabase::calcCombination(unsigned char n, unsigned char r) {
    if (n < r) return 0;
    return (uint64_t)FACTORIAL[n] / ((uint64_t)FACTORIAL[r] * (uint64_t)FACTORIAL[n-r]);
}

uint64_t PatternDatabase::edgeCombinationRank(bool isFirstEdgeGroup, const Cube& cube) const {
    constexpr unsigned char k = NUM_EDGES_IN_GROUP; // 6
    const auto& edgeIdx = isFirstEdgeGroup ? edgesFirstHalf : edgesSecondHalf;

    // Absolute positions (0..11) of this group's edges
    std::array<unsigned char, k> pos{};
    for (unsigned char i = 0; i < k; ++i) {
        pos[i] = cube.getState(
                PieceType::Edge,
                PiecePart::Position,
                cube.getEdgeState(),
                edgeIdx[i]   // which edge piece we’re tracking
        );
    }

    // Sort so we can apply combinatorial number system ranking
    std::sort(pos.begin(), pos.end());

    // C(n, r) accumulation
    uint64_t rank = 0;
    for (unsigned i = 0; i < k; ++i) {
        rank += calcCombination(pos[i], i + 1);
    }

    return rank; // in range 0 .. C(12,6)-1 = 0 .. 923
}

// Combinatorial number system.
//uint64_t PatternDatabase::edgeCombinationRank(bool isFirstEdgeGroup, const Cube& cube) const {
//    uint64_t rank = 0;
//    uint64_t n = TOTAL_NUM_EDGES;
//    uint64_t k = NUM_EDGES_IN_GROUP;
//    const std::array<unsigned char, 6>& edgeIdx = (isFirstEdgeGroup) ? edgesFirstHalf : edgesSecondHalf;
//    std::array<unsigned char, 6> edgePos{};
//    std::transform(edgeIdx.begin(), edgeIdx.end(),
//                   edgePos.begin(),
//                   [&](unsigned char edgeIdx) {
//                            return cube.getState(PieceType::Edge, PiecePart::Position, cube.getEdgeState(), edgeIdx);
//    });
//    std::sort(edgePos.begin(), edgePos.end());
//    for (size_t i = 0; i < k; ++i) {
//        // note: calcCombination(n, r) computes C(n, r)
//        uint64_t test = calcCombination(edgePos[i], i+1);
//        rank += calcCombination(edgePos[i], i+1);
//    }
//    return rank;
//}

uint64_t PatternDatabase::encodePermutationIndex(PieceType pieceType, const Cube& cube, bool isFirstEdgeGroup) const {
    const unsigned char len = (pieceType == PieceType::Corner) ? 8 : 6;
    const uint64_t state = (pieceType == PieceType::Corner) ? cube.getCornerState() : cube.getEdgeState();
    uint64_t perm_index = 0;
    for (unsigned char i = 1; i < len; i++) {
        unsigned char num_larger = 0;
        unsigned char right = (pieceType == PieceType::Corner)
        ? cube.getState(pieceType, PiecePart::Position, state, i)
        : cube.getState(pieceType, PiecePart::Position, state, getEdgeIdx(i,isFirstEdgeGroup));
        for (unsigned char j = 0; j < i; j++) {
            unsigned char left = (pieceType == PieceType::Corner)
            ? cube.getState(pieceType, PiecePart::Position, state, j)
            : cube.getState(pieceType, PiecePart::Position, state, getEdgeIdx(j,isFirstEdgeGroup));
            if (left > right) num_larger++;
        }
        perm_index += num_larger * FACTORIAL[i];
    }
    return perm_index;
}

uint64_t PatternDatabase::oriBaseEncoding(PieceType pieceType, const Cube& cube, bool isFirstEdgeGroup) const {
    unsigned char base = 0, len = 0;
    uint64_t state = 0;
    if(pieceType == PieceType::Corner) {
        base = 3;
        len = 8 - 1; // -1 due to ability to track one less corner
        state = cube.getCornerState();
    } else {
        base = 2;
        len = 6;
        state = cube.getEdgeState();
    }
    uint64_t val = 0;
    for(unsigned char i = 0; i < len; i++) {
        val = (pieceType == PieceType::Corner)
        ? val * base + cube.getState(pieceType, PiecePart::Orientation, state, i)
        : val * base + cube.getState(pieceType, PiecePart::Orientation, state, getEdgeIdx(i,isFirstEdgeGroup));
    }
    return val;
}

uint64_t PatternDatabase::encodeState(PieceType pieceType, const Cube& cube, bool isFirstEdgeGroup) const {
    if(pieceType == PieceType::Corner){
        uint64_t t = encodePermutationIndex(pieceType, cube) * NUM_CORNER_ORIENTATIONS + oriBaseEncoding(pieceType, cube);
        return t;}
//        return encodePermutationIndex(pieceType, cube) * NUM_CORNER_ORIENTATIONS + oriBaseEncoding(pieceType, cube);
    else {
        auto permIndex = (edgeCombinationRank(isFirstEdgeGroup, cube) * NUM_EDGE_PERMUTATIONS + encodePermutationIndex(pieceType, cube, isFirstEdgeGroup));
        return permIndex * NUM_EDGE_ORIENTATIONS + oriBaseEncoding(pieceType, cube, isFirstEdgeGroup);

//        return (edgeCombinationRank(isFirstEdgeGroup, cube) * NUM_EDGE_PERMUTATIONS + encodePermutationIndex(pieceType, cube, isFirstEdgeGroup))
//        * NUM_EDGE_ORIENTATIONS + oriBaseEncoding(pieceType, cube, isFirstEdgeGroup);
    }
}

void PatternDatabase::generatePDB(PieceType pieceType, std::vector<uint8_t>& pdb, unsigned char maxDepth, bool isFirstEdgeGroup) const {
    Cube solved = Cube();
    
    std::queue<std::pair<Cube, unsigned char>> q;
    q.push({solved, 0});
    
    while(!q.empty()) {
        auto [currentCube, currentDepth] = q.front();
        q.pop();
        
        uint64_t idx = encodeState(pieceType, currentCube, isFirstEdgeGroup);
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
    std::ofstream file;
    fs::path filePath = PDBFileHandler::getFilePath(filename);
    file.open(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
    if(file.is_open()){
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
    else {
        std::cerr << filename << " could not be opened." << std::endl;
    }
}

unsigned char PatternDatabase::findMaxDepth(PieceType pieceType, bool isFirstEdgeGroup) const {
    Cube solved = Cube();
    std::queue<std::pair<Cube, unsigned char>> q;
    std::unordered_set<uint64_t> visitedStates;
    q.emplace(solved, 0);
    visitedStates.insert(encodeState(pieceType, solved, isFirstEdgeGroup));

    unsigned char maxDepthFound = 0;

    while (!q.empty()) {
        auto [cube, depth] = q.front();
        q.pop();
        if (depth > maxDepthFound) {
            maxDepthFound = depth;
        }
        for (auto& it : STRING_TO_MOVE) {
            Cube nextCube = cube.move(it.first);
            uint64_t idx = encodeState(pieceType, nextCube, isFirstEdgeGroup);
            if (visitedStates.insert(idx).second) {
                q.push({nextCube, depth + 1});
            }
        }
    }
    return maxDepthFound;
}

void PatternDatabase::findMaxDepths() const {
//    std::cout << "Corner max depth: " << (int)findMaxDepth(PieceType::Corner, true) << std::endl;
    std::cout << "Edge first max depth: " << (int)findMaxDepth(PieceType::Edge, true) << std::endl;
    std::cout << "Edge second max depth: " << (int)findMaxDepth(PieceType::Edge, false) << std::endl;
}

void PatternDatabase::mainPDB() {
//    auto t11 = encodeState(PieceType::Corner, Cube(), true);
//    auto t22 = encodeState(PieceType::Edge, Cube(), true);
//    auto t33 = encodeState(PieceType::Edge, Cube(), false);
//
//    findMaxDepths();
//    std::cout << "FINISHED" << std::endl;
    std::vector<uint8_t> cornerPDB(     CORNER_TOTAL, 0xFF);
    std::vector<uint8_t> startEdgePDB(  EDGE_TOTAL  , 0xFF);
    std::vector<uint8_t> endEdgePDB(    EDGE_TOTAL  , 0xFF);
    std::thread t1([&]() {
        generatePDB(PieceType::Corner, cornerPDB, 15);
    });
    std::thread t2([&]() {
        generatePDB(PieceType::Edge, startEdgePDB, 15, true);
    });
    std::thread t3([&]() {
        generatePDB(PieceType::Edge, endEdgePDB, 15, false);
    });
    t1.join();
    t2.join();
    t3.join();
    saveToFile("corner.pdb",    cornerPDB);
    saveToFile("edge_start.pdb", startEdgePDB);
    saveToFile("edge_end.pdb",   endEdgePDB);
}
//
//PatternDatabase::PatternDatabase(
//    std::array<unsigned char, 6> edgesFirstHalf,
//    std::array<unsigned char, 6> edgesSecondHalf
//    ) :
//    edgesFirstHalf(edgesFirstHalf),
//    edgesSecondHalf(edgesSecondHalf)
//{}