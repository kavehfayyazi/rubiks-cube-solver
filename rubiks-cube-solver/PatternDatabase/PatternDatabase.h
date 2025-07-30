//
//  PatternDatabase.h
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#ifndef PATTERNDATABASE_H
#define PATTERNDATABASE_H

#include "Cube.h"
#include "pieceClassification.h"
#include <array>
#include <cmath>
#include <cstdint>

class PatternDatabase {
private:
    uint64_t factorial(unsigned char n);
    uint64_t factoradic(PieceType pieceType, const Cube& cube);
    uint64_t oriBaseEncoding(PieceType pieceType, const Cube& cube);
    
public:
    uint64_t encodeState(PieceType pieceType, const Cube& cube);
    
private:
    static constexpr uint64_t NUM_CORNER_PERMUTATIONS = 40320;       // 8!
    static constexpr uint64_t NUM_CORNER_ORIENTATIONS = 2187;        // 3^7
    static constexpr uint64_t CORNER_TOTAL = 88179840;               // NUM_CORNER_PERMUTATIONS * NUM_CORNER_ORIENTATIONS

    static constexpr uint64_t NUM_EDGE_PERMUTATIONS = 479001600;     // 12!
    static constexpr uint64_t NUM_EDGE_ORIENTATIONS = 2048;          // 2^11
    static constexpr uint64_t EDGE_TOTAL = 979552051200;             // NUM_EDGE_PERMUTATIONS * NUM_EDGE_ORIENTATIONS
};

#endif
