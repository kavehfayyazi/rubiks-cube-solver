//
//  tables.h
//  src
//
//  Created by Kaveh Fayyazi on 7/26/25.
//

#ifndef RUBIKS_CUBE_SOLVER_MOVETABLES_H
#define RUBIKS_CUBE_SOLVER_MOVETABLES_H

#include "move.h"
#include <unordered_map>
#include <array>

extern const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_PERMED;
extern const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_ORIENTED;

extern const std::unordered_map<Move, std::array<unsigned char, 4>> EDGE_POS_PERMED;
extern const std::unordered_map<Move, std::array<unsigned char, 4>> EDGE_POS_ORIENTED;

#endif