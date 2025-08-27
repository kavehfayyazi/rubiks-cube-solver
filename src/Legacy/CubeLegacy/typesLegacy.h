//
// Created by Kaveh Fayyazi on 8/24/25.
//

#ifndef RUBIKSCUBESOLVER_TYPES_H
#define RUBIKSCUBESOLVER_TYPES_H

#include <cstdint>
#include <string>
#include <map>

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

inline constexpr std::array<Move, MOVE_N> MOVES = {U,U2,U_PRIME,D,D2,D_PRIME,L,L2,L_PRIME,R,R2,R_PRIME,F,F2,F_PRIME,B,B2,B_PRIME,};

// ---------- Cube Enums ----------
enum class PieceType { Corner, Edge };
enum class PiecePart { Position, Orientation };

// ---------- Cube Faces ----------
inline constexpr uint8_t FACES[18] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
inline constexpr uint8_t OPPOSING_FACES[18] = {1,1,1,0,0,0,3,3,3,2,2,2,5,5,5,4,4,4};

// ---------- Cube Mappings ----------
const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_PERMED = {
        {U, {0, 1, 2, 3}}, {U_PRIME, {0, 1, 2, 3}}, {U2, {0, 1, 2, 3}},
        {D, {4, 5, 6, 7}}, {D_PRIME, {4, 5, 6, 7}}, {D2, {4, 5, 6, 7}},
        {L, {1, 0, 4, 7}}, {L_PRIME, {1, 0, 4, 7}}, {L2, {1, 0, 4, 7}},
        {R, {3, 2, 6, 5}}, {R_PRIME, {3, 2, 6, 5}}, {R2, {3, 2, 6, 5}},
        {F, {0, 3, 5, 4}}, {F_PRIME, {0, 3, 5, 4}}, {F2, {0, 3, 5, 4}},
        {B, {2, 1, 7, 6}}, {B_PRIME, {2, 1, 7, 6}}, {B2, {2, 1, 7, 6}},
};

const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_ORIENTED = {
        {L, {1, 0, 4, 7}}, {L_PRIME, {1, 0, 4, 7}},
        {R, {3, 2, 6, 5}}, {R_PRIME, {3, 2, 6, 5}},
        {F, {0, 3, 5, 4}}, {F_PRIME, {0, 3, 5, 4}},
        {B, {2, 1, 7, 6}}, {B_PRIME, {2, 1, 7, 6}},
};

const std::unordered_map<Move, std::array<unsigned char, 4>> EDGE_POS_PERMED = {
        {U, {0, 1, 2, 3}},   {U_PRIME, {0, 1, 2, 3}},   {U2, {0, 1, 2, 3}},
        {D, {4, 5, 6, 7}},   {D_PRIME, {4, 5, 6, 7}},   {D2, {4, 5, 6, 7}},
        {L, {1, 8, 7, 11}},  {L_PRIME, {1, 8, 7, 11}},  {L2, {1, 8, 7, 11}},
        {R, {3, 10, 5, 9}},  {R_PRIME, {3, 10, 5, 9}},  {R2, {3, 10, 5, 9}},
        {F, {0, 9, 4, 8}},   {F_PRIME, {0, 9, 4, 8}},   {F2, {0, 9, 4, 8}},
        {B, {2, 11, 6, 10}}, {B_PRIME, {2, 11, 6, 10}}, {B2, {2, 11, 6, 10}},
};

const std::unordered_map<Move, std::array<unsigned char, 4>> EDGE_POS_ORIENTED = {
        {F, {0, 9, 4, 8}}, {F_PRIME, {0, 9, 4, 8}},
        {B, {2,11, 6,10}}, {B_PRIME, {2,11, 6,10}},
};

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

#endif //RUBIKSCUBESOLVER_TYPES_H
