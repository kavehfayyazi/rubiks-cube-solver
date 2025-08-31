//
// Created by Kaveh Fayyazi on 8/28/25.
//

#include "solve.h"
#include <stdexcept>
#include "cube.h"
#include "ida_star.h"

using MoveList = std::vector<Move>;

void solveScramble(int n, MoveList& scramble, MoveList& solve) {
    scramble.clear(); solve.clear();
    Cube c = Cube();
    scramble = c.genScramble(n);
    c.doMoves(scramble);
    IDAStar ida = IDAStar();
    ida.solve(c, solve);
    c.doMoves(solve);
    if (!c.is_solved()) throw std::runtime_error("Error with solver.");
}