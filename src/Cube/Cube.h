//
//  Cube.h
//  src
//
//  Created by Kaveh Fayyazi on 7/25/25.
//

#ifndef RUBIKS_CUBE_SOLVER_CUBE_H
#define RUBIKS_CUBE_SOLVER_CUBE_H

#include "types.h"
#include <array>
#include <string>
#include <cstdint>
#include <cstddef>

class Cube {
private:
    uint8_t cp[CORNERS_N];  // corner permutation: which corner is at position i
    uint8_t co[CORNERS_N];  // corner orientation: 0,1,2
    uint8_t ep[EDGES_N]; // edge permutation
    uint8_t eo[EDGES_N]; // edge orientation: 0/1

    uint8_t edgesFirstHalf[HALF_EDGES_N] = {0,1,2,3,8,9};
    uint8_t edgesSecondHalf[HALF_EDGES_N] = {4,5,6,7,10,11};

public:
    // ---- Constructors ----
    Cube(); // Default constructor initalizes solved state
    Cube(const uint8_t cp_[CORNERS_N], const uint8_t co_[CORNERS_N], const uint8_t ep_[EDGES_N], const uint8_t eo_[EDGES_N]);

    // ---- Core operations ----
    void doMove (Move move);
    void undoMove (Move move);
    void doMoves(const std::vector<Move>& moves);
    std::vector<Move> genScramble(int n) const;
    bool is_solved() const;

    // ---- Encoding ----
    uint64_t encodeCorners() const;
    uint64_t encodeFirstEdges() const;
    uint64_t encodeSecondEdges() const;

    // ---- Operators ----
    bool operator==(const Cube& other) const;
};

#endif
