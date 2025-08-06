//
//  IDAStar.h
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 8/4/25.
//

#ifndef IDASTAR_H
#define IDASTAR_H

#include "Cube.h"
#include <vector>

struct Result {
    bool found;
    size_t nextThreshold; // if found==false
};

class IDAStar {
private:
    size_t calculateHeuristic(Cube c);
    std::vector<Cube> getSuccessors(Cube c);
    Result search(std::vector<Cube>& searchPath, size_t g, size_t bound);

public:
    bool solve(Cube root, std::vector<Cube>& solutionPath);
};

#endif
