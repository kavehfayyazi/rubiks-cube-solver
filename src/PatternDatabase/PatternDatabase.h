//
//  PatternDatabase.cpp
//  src
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#ifndef RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H

#include "pieceClassification.h"
#include "Cube.h"
#include <cstddef>
#include <vector>
#include <optional>
#include <atomic>
#include <array>
#include <cstdint>

class PatternDatabase {
private:
    unsigned char getEdgeIdx(unsigned char idx, bool isFirstEdgeGroup) const;

    static uint64_t getPDBVal(std::vector<uint8_t>& pdb, uint64_t idx);
    static void setPDBVal(std::vector<uint8_t>& pdb, uint64_t idx, unsigned char val);

    static constexpr uint64_t calcCombination(unsigned char n, unsigned char r);
    uint64_t edgeCombinationRank(bool isFirstEdgeGroup, const Cube& cube) const;
    uint64_t encodePermutationIndex(PieceType pieceType, const Cube& cube, bool isFirstEdgeGroup = true) const;
    uint64_t oriBaseEncoding(PieceType pieceType, const Cube& cube, bool isFirstEdgeGroup = true) const;

    void generatePDB(PieceType pieceType, std::vector<uint8_t>& pdb, unsigned char maxDepth, bool isFirstEdgeGroup = true) const;

public:
    static bool isHighNibble(uint64_t idx);
    uint64_t encodeState(PieceType pieceType, const Cube& cube, bool isFirstEdgeGroup = true) const;
    void saveToFile(const std::string& filename, const std::vector<uint8_t>& data);
    void mainPDB();

private:
    unsigned char findMaxDepth(PieceType pieceType, bool isFirstEdgeGroup) const;
    void findMaxDepths() const;

private:
    static constexpr std::array<uint64_t, 12> FACTORIAL = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800}; // 0-11
    inline static std::atomic<size_t> visited;

    static constexpr uint64_t NUM_CORNER_PERMUTATIONS = FACTORIAL[8];
    static constexpr uint64_t NUM_CORNER_ORIENTATIONS = 2187;
    static constexpr uint64_t CORNER_RAW = NUM_CORNER_PERMUTATIONS * NUM_CORNER_ORIENTATIONS;
    static constexpr uint64_t CORNER_TOTAL = CORNER_RAW / 2;

    static constexpr uint64_t TOTAL_NUM_EDGES = 12;
    static constexpr uint64_t NUM_EDGES_IN_GROUP = 6;
    static constexpr uint64_t NUM_EDGE_COMBINATIONS = 924;              // C(12,6)
    static constexpr uint64_t NUM_EDGE_PERMUTATIONS = 720;
    static constexpr uint64_t NUM_EDGE_ORIENTATIONS = 64;
    static constexpr uint64_t EDGE_TOTAL_RAW = NUM_EDGE_COMBINATIONS * NUM_EDGE_PERMUTATIONS * NUM_EDGE_ORIENTATIONS;
    static constexpr uint64_t EDGE_TOTAL = EDGE_TOTAL_RAW / 2;

public:
    std::array<unsigned char, 6> edgesFirstHalf = {0,1,2,3,8,9};
    std::array<unsigned char, 6> edgesSecondHalf = {4,5,6,7,10,11};
};

#endif