//
//  move.h
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/26/25.
//

#ifndef MOVE_H
#define MOVE_H
#include <unordered_map>
#include <string>

enum Move : unsigned char {
    U=0, U2=1, U_PRIME=2,
    D=3, D2=4, D_PRIME=5,
    L=6, L2=7, L_PRIME=8,
    R=9, R2=10, R_PRIME=11,
    F=12, F2=13, F_PRIME=14,
    B=15, B2=16, B_PRIME=17,
    MOVE_N=18 // Sentinel value
};

const std::unordered_map<std::string, Move> STRING_TO_MOVE {
    {"U",   Move::U},
    {"U'",  Move::U_PRIME},
    {"U2",  Move::U2},
    {"D",   Move::D},
    {"D'",  Move::D_PRIME},
    {"D2",  Move::D2},
    {"L",   Move::L},
    {"L'",  Move::L_PRIME},
    {"L2",  Move::L2},
    {"R",   Move::R},
    {"R'",  Move::R_PRIME},
    {"R2",  Move::R2},
    {"F",   Move::F},
    {"F'",  Move::F_PRIME},
    {"F2",  Move::F2},
    {"B",   Move::B},
    {"B'",  Move::B_PRIME},
    {"B2",  Move::B2},
};

const std::unordered_map<int, std::string> CODE_TO_MOVE_STRING {
    {0, "U"},
    {1, "U'"},
    {2, "U2"},
    {3, "D"},
    {4, "D'"},
    {5, "D2"},
    {6, "L"},
    {7, "L'"},
    {8, "L2"},
    {9, "R"},
    {10, "R'"},
    {11, "R2"},
    {12, "F"},
    {13, "F'"},
    {14, "F2"},
    {15, "B"},
    {16, "B'"},
    {17, "B2"},
};



#include <unordered_map>
#include <array>

extern const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_PERMED;




#endif
