//
// Created by Kaveh Fayyazi on 8/27/25.
//

#ifndef RUBIKSCUBESOLVER_PDB_CONSTANTS_H
#define RUBIKSCUBESOLVER_PDB_CONSTANTS_H

#include <cstdint>

static constexpr uint64_t NUM_CORNER_PERMUTATIONS   = 40320; // 8!
static constexpr uint64_t NUM_CORNER_ORIENTATIONS   = 2187;  // 3^7
static constexpr uint64_t CORNER_STATES             = NUM_CORNER_PERMUTATIONS * NUM_CORNER_ORIENTATIONS;
static constexpr uint64_t CORNER_PDB_BYTES          = (CORNER_STATES + 1) / 2;

static constexpr uint64_t NUM_EDGE_COMBINATIONS     = 924; // C(12,6)
static constexpr uint64_t NUM_EDGE_PERMUTATIONS     = 720; // 6!
static constexpr uint64_t NUM_EDGE_ORIENTATIONS     = 64;  // 2^6
static constexpr uint64_t EDGE_STATES               = NUM_EDGE_COMBINATIONS * NUM_EDGE_PERMUTATIONS * NUM_EDGE_ORIENTATIONS;
static constexpr uint64_t EDGE_PDB_BYTES            = (EDGE_STATES + 1) / 2;

#endif //RUBIKSCUBESOLVER_PDB_CONSTANTS_H
