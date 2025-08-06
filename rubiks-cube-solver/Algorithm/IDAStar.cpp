//
// Created by Kaveh Fayyazi on 8/4/25.
//

#include "IDAStar.h"
#include "pieceClassification.h"
#include <limits.h>

size_t IDAStar::calculateHeuristic(Cube c) {
    return
}

std::vector<Cube> IDAStar::getSuccessors(Cube c) {
    std::vector<Cube> successors;
    for(auto& it: STRING_TO_MOVE) {
        successors.push_back(c.move(it.first));
    }
    return successors;
}

Result IDAStar::search(std::vector<Cube>& searchPath, size_t g, size_t bound) {
    Cube node = searchPath.back();
    size_t f = g + calculateHeuristic(node);
    if(f > bound) return Result{false, f};
    if(node.is_solved()) return Result{true, 0};
    size_t minNextThreshold = SIZE_MAX;
    for(Cube next : getSuccessors(node)) {
        auto it = std::find(searchPath.begin(), searchPath.end(), next);
        if(it == searchPath.end()) { // The next cube is not in the stack.
            searchPath.push_back(next);
            Result t = search(searchPath, g + 1, bound);
            if(t.found) return Result{true, 0};
            if(t.nextThreshold < minNextThreshold)
                minNextThreshold = t.nextThreshold;
            searchPath.pop_back();
        }
    }
    return Result{false, minNextThreshold};
}

bool IDAStar::solve(Cube root, std::vector<Cube>& solutionPath) {
    std::vector<Cube> searchPath;
    searchPath.push_back(root);
    size_t bound = calculateHeuristic(root);
    while(true) {
        Result t = search(searchPath, 0, bound);
        if(t.found) {
            solutionPath.swap(searchPath);
            return true;
        }
        if(t.nextThreshold == SIZE_MAX) return false;
        bound = t.nextThreshold;
    }
}