//
//  tables.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/26/25.
//

#include "moveTables.h"

const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_PERMED = {
    {Move::U, {0, 1, 2, 3}},
    {Move::U_PRIME, {0, 1, 2, 3}},
    {Move::U2, {0, 1, 2, 3}},
    {Move::D, {4, 5, 6, 7}},
    {Move::D_PRIME, {4, 5, 6, 7}},
    {Move::D2, {4, 5, 6, 7}},
    {Move::L, {1, 0, 4, 7}},
    {Move::L_PRIME, {1, 0, 4, 7}},
    {Move::L2, {1, 0, 4, 7}},
    {Move::R, {3, 2, 6, 5}},
    {Move::R_PRIME, {3, 2, 6, 5}},
    {Move::R2, {3, 2, 6, 5}},
    {Move::F, {0, 3, 5, 4}},
    {Move::F_PRIME, {0, 3, 5, 4}},
    {Move::F2, {0, 3, 5, 4}},
    {Move::B, {2, 1, 7, 6}},
    {Move::B_PRIME, {2, 1, 7, 6}},
    {Move::B2, {2, 1, 7, 6}},
};

const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_ORIENTED = {
    {Move::L, {1, 0, 4, 7}},
    {Move::L_PRIME, {1, 0, 4, 7}},
    {Move::R, {3, 2, 6, 5}},
    {Move::R_PRIME, {3, 2, 6, 5}},
    {Move::F, {0, 3, 5, 4}},
    {Move::F_PRIME, {0, 3, 5, 4}},
    {Move::B, {2, 1, 7, 6}},
    {Move::B_PRIME, {2, 1, 7, 6}},
};

const std::unordered_map<Move, std::array<unsigned char, 4>> EDGE_POS_PERMED = {
    {Move::U, {0, 1, 2, 3}},
    {Move::U_PRIME, {0, 1, 2, 3}},
    {Move::U2, {0, 1, 2, 3}},
    {Move::D, {4, 5, 6, 7}},
    {Move::D_PRIME, {4, 5, 6, 7}},
    {Move::D2, {4, 5, 6, 7}},
    {Move::L, {1, 8, 7, 11}},
    {Move::L_PRIME, {1, 8, 7, 11}},
    {Move::L2, {1, 8, 7, 11}},
    {Move::R, {3, 10, 5, 9}},
    {Move::R_PRIME, {3, 10, 5, 9}},
    {Move::R2, {3, 10, 5, 9}},
    {Move::F, {0, 9, 4, 8}},
    {Move::F_PRIME, {0, 9, 4, 8}},
    {Move::F2, {0, 9, 4, 8}},
    {Move::B, {2, 11, 6, 10}},
    {Move::B_PRIME, {2, 11, 6, 10}},
    {Move::B2, {2, 11, 6, 10}},
};

const std::unordered_map<Move, std::array<unsigned char, 12>> EDGE_POS_ORIENTED = {
    {Move::L, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
    {Move::L_PRIME, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
    {Move::R, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
    {Move::R_PRIME, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
};
