//
// Created by Kaveh Fayyazi on 8/24/25.
//

#ifndef RUBIKSCUBESOLVER_TYPES_H
#define RUBIKSCUBESOLVER_TYPES_H

#include <cstdint>
#include <string>
#include <map>
#include <array>
#include <unordered_map>

// ---------- Move Enum ----------
enum Move : uint8_t {
    U=0,  U2=1,  U_PRIME=2,
    D=3,  D2=4,  D_PRIME=5,
    L=6,  L2=7,  L_PRIME=8,
    R=9,  R2=10, R_PRIME=11,
    F=12, F2=13, F_PRIME=14,
    B=15, B2=16, B_PRIME=17,
    MOVE_N=18 // Sentinel value
};

inline constexpr std::array<Move, MOVE_N> MOVES = {U,U2,U_PRIME,D,D2,D_PRIME,L,L2,L_PRIME,R,R2,R_PRIME,F,F2,F_PRIME,B,B2,B_PRIME};

// ---------- Cube Mappings ----------

static inline constexpr uint8_t CORNERS_N = 8;
static inline constexpr uint8_t EDGES_N = 12;
static inline constexpr uint8_t HALF_EDGES_N = 6;

enum C { ULF=0, ULB=1, URB=2, URF=3, DLF=4, DRF=5, DRB=6, DLB=7 };                   // Corner indices
enum E { UF=0, UL=1, UB=2, UR=3, DF=4, DR=5, DB=6, DL=7, LF=8, RF=9, RB=10, LB=11 }; // Edge indices

static inline constexpr uint8_t cp_[MOVE_N][CORNERS_N] {
    {URF, ULF, ULB, URB, DLF, DRF, DRB, DLB}, // U
    {URB, URF, ULF, ULB, DLF, DRF, DRB, DLB}, // U2
    {ULB, URB, URF, ULF, DLF, DRF, DRB, DLB}, // U'
    {ULF, ULB, URB, URF, DLB, DLF, DRF, DRB}, // D
    {ULF, ULB, URB, URF, DRB, DLB, DLF, DRF}, // D2
    {ULF, ULB, URB, URF, DRF, DRB, DLB, DLF}, // D'
    {ULB, DLB, URB, URF, ULF, DRF, DRB, DLF}, // L
    {DLB, DLF, URB, URF, ULB, DRF, DRB, ULF}, // L2
    {DLF, ULF, URB, URF, DLB, DRF, DRB, ULB}, // L'
    {ULF, ULB, URF, DRF, DLF, DRB, URB, DLB}, // R
    {ULF, ULB, DRF, DRB, DLF, URB, URF, DLB}, // R2
    {ULF, ULB, DRB, URB, DLF, URF, DRF, DLB}, // R'
    {DLF, ULB, URB, ULF, DRF, URF, DRB, DLB}, // F
    {DRF, ULB, URB, DLF, URF, ULF, DRB, DLB}, // F2
    {URF, ULB, URB, DRF, ULF, DLF, DRB, DLB}, // F'
    {ULF, URB, DRB, URF, DLF, DRF, DLB, ULB}, // B
    {ULF, DRB, DLB, URF, DLF, DRF, ULB, URB}, // B2
    {ULF, DLB, ULB, URF, DLF, DRF, URB, DRB}, // B'
};

static inline constexpr uint8_t co_[MOVE_N][CORNERS_N] = {
    {0,0,0,0,0,0,0,0}, // U
    {0,0,0,0,0,0,0,0}, // U2
    {0,0,0,0,0,0,0,0}, // U'
    {0,0,0,0,0,0,0,0}, // D
    {0,0,0,0,0,0,0,0}, // D2
    {0,0,0,0,0,0,0,0}, // D'
    {1,2,0,0,2,0,0,1}, // L
    {0,0,0,0,0,0,0,0}, // L2
    {1,2,0,0,2,0,0,1}, // L'
    {0,0,1,2,0,1,2,0}, // R
    {0,0,0,0,0,0,0,0}, // R2
    {0,0,1,2,0,1,2,0}, // R'
    {2,0,0,1,1,2,0,0}, // F
    {0,0,0,0,0,0,0,0}, // F2
    {2,0,0,1,1,2,0,0}, // F'
    {0,1,2,0,0,0,1,2}, // B
    {0,0,0,0,0,0,0,0}, // B2
    {0,1,2,0,0,0,1,2}, // B'
};

static inline constexpr uint8_t ep_[MOVE_N][EDGES_N] = {
    {UR, UF, UL, UB, DF, DR, DB, DL, LF, RF, RB, LB}, // U
    {UB, UR, UF, UL, DF, DR, DB, DL, LF, RF, RB, LB}, // U2
    {UL, UB, UR, UF, DF, DR, DB, DL, LF, RF, RB, LB}, // U'
    {UF, UL, UB, UR, DL, DF, DR, DB, LF, RF, RB, LB}, // D
    {UF, UL, UB, UR, DB, DL, DF, DR, LF, RF, RB, LB}, // D2
    {UF, UL, UB, UR, DR, DB, DL, DF, LF, RF, RB, LB}, // D'
    {UF, LB, UB, UR, DF, DR, DB, LF, UL, RF, RB, DL}, // L
//    UF, UL, UB, UR, DF, DR, DB, DL, LF, RF, RB, LB }; // Edge indices
    {UF, DL, UB, UR, DF, DR, DB, UL, LB, RF, RB, LF}, // L2
    {UF, LF, UB, UR, DF, DR, DB, LB, DL, RF, RB, UL}, // L'
    {UF, UL, UB, RF, DF, RB, DB, DL, LF, DR, UR, LB}, // R
    {UF, UL, UB, DR, DF, UR, DB, DL, LF, RB, RF, LB}, // R2
    {UF, UL, UB, RB, DF, RF, DB, DL, LF, UR, DR, LB}, // R'
    {LF, UL, UB, UR, RF, DR, DB, DL, DF, UF, RB, LB}, // F
    {DF, UL, UB, UR, UF, DR, DB, DL, RF, LF, RB, LB}, // F2
    {RF, UL, UB, UR, LF, DR, DB, DL, UF, DF, RB, LB}, // F'
    {UF, UL, RB, UR, DF, DR, LB, DL, LF, RF, DB, UB}, // B
    {UF, UL, DB, UR, DF, DR, UB, DL, LF, RF, LB, RB}, // B2
    {UF, UL, LB, UR, DF, DR, RB, DL, LF, RF, UB, DB}, // B'
};

static inline constexpr uint8_t eo_[MOVE_N][EDGES_N] = {
    {0,0,0,0,0,0,0,0,0,0,0,0}, // U
    {0,0,0,0,0,0,0,0,0,0,0,0}, // U2
    {0,0,0,0,0,0,0,0,0,0,0,0}, // U'
    {0,0,0,0,0,0,0,0,0,0,0,0}, // D
    {0,0,0,0,0,0,0,0,0,0,0,0}, // D2
    {0,0,0,0,0,0,0,0,0,0,0,0}, // D'
    {0,0,0,0,0,0,0,0,0,0,0,0}, // L
    {0,0,0,0,0,0,0,0,0,0,0,0}, // L2
    {0,0,0,0,0,0,0,0,0,0,0,0}, // L'
    {0,0,0,0,0,0,0,0,0,0,0,0}, // R
    {0,0,0,0,0,0,0,0,0,0,0,0}, // R2
    {0,0,0,0,0,0,0,0,0,0,0,0}, // R'
    {1,0,0,0,1,0,0,0,1,1,0,0}, // F
    {0,0,0,0,0,0,0,0,0,0,0,0}, // F2
    {1,0,0,0,1,0,0,0,1,1,0,0}, // F'
    {0,0,1,0,0,0,1,0,0,0,1,1}, // B
    {0,0,0,0,0,0,0,0,0,0,0,0}, // B2
    {0,0,1,0,0,0,1,0,0,0,1,1}, // B'
};

static inline constexpr Move INVERSE[MOVE_N] = {U_PRIME,U2,U,D_PRIME,D2,D,L_PRIME,L2,L,R_PRIME,R2,R,F_PRIME,F2,F,B_PRIME,B2,B};

// ---------- Cube Faces ----------
inline constexpr uint8_t FACES[18] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
inline constexpr uint8_t OPPOSING_FACES[18] = {1,1,1,0,0,0,3,3,3,2,2,2,5,5,5,4,4,4};

// ---------- Move Castings ----------
inline const std::unordered_map<std::string, Move> STRING_TO_MOVE {
        {"U", U}, {"U2", U2}, {"U'", U_PRIME},
        {"D", D}, {"D2", D2}, {"D'", D_PRIME},
        {"L", L}, {"L2", L2}, {"L'", L_PRIME},
        {"R", R}, {"R2", R2}, {"R'", R_PRIME},
        {"F", F}, {"F2", F2}, {"F'", F_PRIME},
        {"B", B}, {"B2", B2}, {"B'", B_PRIME},
};

inline const std::unordered_map<Move, std::string> MOVE_TO_STRING {
        {U,  "U"}, {U2, "U2"}, {U_PRIME, "U'"},
        {D,  "D"}, {D2, "D2"}, {D_PRIME, "D'"},
        {L,  "L"}, {L2, "L2"}, {L_PRIME, "L'"},
        {R,  "R"}, {R2, "R2"}, {R_PRIME, "R'"},
        {F,  "F"}, {F2, "F2"}, {F_PRIME, "F'"},
        {B,  "B"}, {B2, "B2"}, {B_PRIME, "B'"},
};

inline const std::unordered_map<int, std::string> CODE_TO_MOVE_STRING {
        {0,  "U"}, {1,  "U2"}, {2,  "U'"},
        {3,  "D"}, {4,  "D2"}, {5,  "D'"},
        {6,  "L"}, {7,  "L2"}, {8,  "L'"},
        {9,  "R"}, {10, "R2"}, {11, "R'"},
        {12, "F"}, {13, "F2"}, {14, "F'"},
        {15, "B"}, {16, "B2"}, {17, "B'"},
};



// ---------- Solved Cube ----------
static inline constexpr uint8_t solvedCp[CORNERS_N] = {0,1,2,3,4,5,6,7};
static inline constexpr uint8_t solvedCo[CORNERS_N] = {0,0,0,0,0,0,0,0};
static inline constexpr uint8_t solvedEp[EDGES_N] = {0,1,2,3,4,5,6,7,8,9,10,11};
static inline constexpr uint8_t solvedEo[EDGES_N] = {0,0,0,0,0,0,0,0,0,0,0,0};

inline constexpr std::array<uint64_t, 12> FACTORIAL = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800}; // 0-11


static constexpr uint64_t NUM_CORNER_PERMUTATIONS = FACTORIAL[8];
static constexpr uint64_t NUM_CORNER_ORIENTATIONS = 2187;
static constexpr uint64_t CORNER_STATES = NUM_CORNER_PERMUTATIONS * NUM_CORNER_ORIENTATIONS;
static constexpr uint64_t CORNER_PDB_BYTES = (CORNER_STATES + 1) / 2;

static constexpr uint64_t NUM_EDGE_COMBINATIONS = 924; // C(12,6)
static constexpr uint64_t NUM_EDGE_PERMUTATIONS = 720; // 6!
static constexpr uint64_t NUM_EDGE_ORIENTATIONS = 64;  // 2^6
static constexpr uint64_t EDGE_STATES = NUM_EDGE_COMBINATIONS * NUM_EDGE_PERMUTATIONS * NUM_EDGE_ORIENTATIONS;
static constexpr uint64_t EDGE_PDB_BYTES = (EDGE_STATES + 1) / 2;


#endif //RUBIKSCUBESOLVER_TYPES_H
