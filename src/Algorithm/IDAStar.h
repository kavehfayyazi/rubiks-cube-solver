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
    static void getSuccessors(const Cube& c, std::vector<Cube>& successors);
    Result search(std::vector<Cube>& searchPath, std::vector<Move>& movePath, size_t g, size_t bound) const;

public:
    IDAStar();
    bool solve(Cube root, std::vector<Move>& moveSolution) const;

private:
    PatternDatabase pdb;
    PDBFileHandler corner;
    PDBFileHandler edge_start;
    PDBFileHandler edge_end;
};

#endif
