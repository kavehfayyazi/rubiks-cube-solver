//
// Created by Kaveh Fayyazi on 8/28/25.
//

#ifndef RUBIKSCUBESOLVER_SOLVE_H
#define RUBIKSCUBESOLVER_SOLVE_H

#include "move.h"
#include <vector>

using MoveList = std::vector<Move>;

void solveScramble(int n, MoveList& scramble, MoveList& solve);

#endif //RUBIKSCUBESOLVER_SOLVE_H
