//
//  IDAStar.h
//  Src
//
//  Created by Kaveh Fayyazi on 8/4/25.
//

#ifndef IDASTAR_H
#define IDASTAR_H

#include "cube.h"
#include "pdb_handler.h"

using MoveList = std::vector<Move>;

struct TTEntry { uint16_t best_g; };

struct Result {
    bool found;
    size_t nextThreshold; // if found==false
};

class IDAStar {
public:
    uint8_t calculateHeuristic(const Cube& c) const;
    bool multiLevelHeuristic(const Cube& c, size_t& f, const size_t& g, const size_t bound) const;
    Result search(Cube& cube, std::vector<Move>& movePath, size_t g, size_t bound, Move last, Move last2, std::unordered_map<uint64_t, TTEntry>* tt) const;
    static void condenseMoves(std::vector<Move>& movePath);

public:
    IDAStar();
    bool solve(Cube root, std::vector<Move>& moveSolution) const;
    void solveScramble(int n, MoveList& scramble, MoveList& solve) const;

private:
    PdbHandler corner;
    PdbHandler edgeStart;
    PdbHandler edgeEnd;
};

#endif
