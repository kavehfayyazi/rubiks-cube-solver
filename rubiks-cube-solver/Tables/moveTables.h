//
//  tables.h
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/26/25.
//

#ifndef MOVETABLES_H
#define MOVETABLES_H

#include "move.h"
#include <unordered_map>
#include <array>

extern const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_PERMED;
extern const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_ORIENTED;

extern const std::unordered_map<Move, std::array<unsigned char, 4>> EDGE_POS_PERMED;
extern const std::unordered_map<Move, std::array<unsigned char, 12>> EDGE_POS_ORIENTED;

#endif
