//
//  IDAStar.h
//  src
//
//  Created by Kaveh Fayyazi on 8/4/25.
//

#ifndef IDASTAR_H
#define IDASTAR_H

#include "Cube.h"
#include "PatternDatabase.h"
#include "PDBFileHandler.h"
#include <vector>
#include <array>

struct Result {
    bool found;
    size_t nextThreshold; // if found==false
};

class IDAStar {
private:
    size_t calculateHeuristic(const Cube& c) const;
    inline bool multiLevelHeuristic(const Cube& c, size_t& f, const size_t& g, const size_t bound) const;
    Result search(Cube& cube, std::vector<Move>& movePath, size_t g, size_t bound, Move last = MOVE_N) const;

public:
    static void condenseMoves(std::vector<Move>& movePath);
    IDAStar();
    bool solve(Cube root, std::vector<Move>& moveSolution) const;

private:
    PatternDatabase pdb;
    PDBFileHandler corner;
    PDBFileHandler edge_start;
    PDBFileHandler edge_end;
};

#endif
