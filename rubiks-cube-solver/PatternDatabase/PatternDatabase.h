//
//  PatternDatabase.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#include "pieceClassification.h"
#include "Cube.h"
#include <vector>
#include <optional>
#include <atomic>
#include <array>
#include <cstdint>
#include <cstddef>

class PatternDatabase {
private:
    void checkEdges(PieceType pieceType, const std::optional<std::array<unsigned char, 6>>& edgesArr) const;
    bool isHighNibble(uint64_t idx) const;
    uint64_t getPDBVal(std::vector<uint8_t>& pdb, uint64_t idx) const;
    void setPDBVal(std::vector<uint8_t>& pdb, uint64_t idx, unsigned char val);

    uint64_t encodePermutationIndex(PieceType pieceType, const Cube& cube, const std::optional<std::array<unsigned char, 6>>& edgesArr) const;
    uint64_t oriBaseEncoding(PieceType pieceType, const Cube& cube, const std::optional<std::array<unsigned char, 6>>& edgesArr) const;
    uint64_t encodeState(PieceType pieceType, const Cube& cube, const std::optional<std::array<unsigned char, 6>>& edgesArr) const;
    void generatePDB(PieceType pieceType, std::vector<uint8_t>& pdb, unsigned char maxDepth, const std::optional<std::array<unsigned char, 6>>& edgesArr = std::nullopt);

public:
    void saveToFile(const std::string& filename, const std::vector<uint8_t>& data);
    void mainPDB();

private:
    static std::atomic<size_t> visited;
    static constexpr std::array<uint64_t, 9> FACTORIAL = {1,1,2,6,24,120,720,5040,40320}; // 0-8

    static constexpr uint64_t NUM_CORNER_PERMUTATIONS = FACTORIAL[8];
    static constexpr uint64_t NUM_CORNER_ORIENTATIONS = 2187;
    static constexpr uint64_t CORNER_TOTAL = NUM_CORNER_PERMUTATIONS * NUM_CORNER_ORIENTATIONS;

    static constexpr uint64_t NUM_EDGE_PERMUTATIONS = FACTORIAL[6];
    static constexpr uint64_t NUM_EDGE_ORIENTATIONS = 64;
    static constexpr uint64_t EDGE_TOTAL = NUM_EDGE_PERMUTATIONS * NUM_EDGE_ORIENTATIONS;
};
