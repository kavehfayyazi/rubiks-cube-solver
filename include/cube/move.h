//
// Created by Kaveh Fayyazi on 8/27/25.
//

#ifndef RUBIKSCUBESOLVER_MOVE_H
#define RUBIKSCUBESOLVER_MOVE_H

#include <cstdint>
#include <array>
#include <unordered_map>

enum Move : uint8_t {
    U=0,  U2=1,  U_PRIME=2,
    D=3,  D2=4,  D_PRIME=5,
    L=6,  L2=7,  L_PRIME=8,
    R=9,  R2=10, R_PRIME=11,
    F=12, F2=13, F_PRIME=14,
    B=15, B2=16, B_PRIME=17,
    MOVE_N=18
};

inline constexpr uint8_t NUM_FACES = 6;
inline constexpr uint8_t CORNERS_N = 8;
inline constexpr uint8_t EDGES_N = 12;
inline constexpr uint8_t HALF_EDGES_N = 6;

enum C { ULF=0, ULB=1, URB=2, URF=3, DLF=4, DRF=5, DRB=6, DLB=7 };                   // Corner indices
enum E { UF=0, UL=1, UB=2, UR=3, DF=4, DR=5, DB=6, DL=7, LF=8, RF=9, RB=10, LB=11 }; // Edge indices

// Declarations (defined in move.cpp)
extern const std::array<Move, MOVE_N> MOVES;
extern const std::array<Move, MOVE_N> INVERSE;
extern const std::array<std::array<Move, 4>, NUM_FACES> GET_MOVE;
extern const std::array<uint8_t, MOVE_N> GET_TURNS;

extern const std::array<uint8_t, MOVE_N> FACES;
extern const std::array<uint8_t, MOVE_N> OPPOSING_FACES;

extern const std::array<std::array<uint8_t, CORNERS_N>, MOVE_N> cp_;
extern const std::array<std::array<uint8_t, CORNERS_N>, MOVE_N> co_;
extern const std::array<std::array<uint8_t, EDGES_N>,   MOVE_N> ep_;
extern const std::array<std::array<uint8_t, EDGES_N>,   MOVE_N> eo_;

extern const std::unordered_map<Move, std::string> MOVE_TO_STRING;
extern const std::unordered_map<std::string, Move> STRING_TO_MOVE;

// Small helpers that depend on arrays above
uint8_t face(Move a);
bool isSameFace(Move a, Move b);
bool isOpposingFace(Move a, Move b);
uint8_t getNumTurns(Move m);
Move getMove(uint8_t f, uint8_t t);

#endif //RUBIKSCUBESOLVER_MOVE_H
