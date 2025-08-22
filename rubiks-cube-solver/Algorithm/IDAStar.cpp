//
// Created by Kaveh Fayyazi on 8/4/25.
//

#include "IDAStar.h"
#include <cstdint>

size_t IDAStar::calculateHeuristic(const Cube& c) const {
    unsigned char cH = corner.search(pdb.encodeState(PieceType::Corner, c));
    unsigned char e1H = edge_start.search(pdb.encodeState(PieceType::Edge, c, true));
    unsigned char e2H = edge_end.search(pdb.encodeState(PieceType::Edge, c, false));
    return cH + e1H + e2H;
}

void IDAStar::getSuccessors(const Cube& c, std::vector<Cube>& successors) {
    successors.clear();
    successors.reserve(MOVE_N);
    for(auto& it: STRING_TO_MOVE) {
        Cube next = c.move(it.first);
        successors.push_back(next);
    }
}

Result IDAStar::search(std::vector<Cube>& searchPath, std::vector<Move>& movePath, size_t g, size_t bound) const {
    const Cube &node = searchPath.back();

    if (node.is_solved()) return Result{true, 0};

    size_t f = g + calculateHeuristic(node);
    if (f > bound) return Result{false, f};

    size_t minNextThreshold = SIZE_MAX;

    std::vector<Cube> successors;
    getSuccessors(node, successors);

    // going through successors in step with string to move

    size_t MoveIdx = 0;
    for (const auto &kv: STRING_TO_MOVE) {
        const Move mv = kv.second;
        const Cube &next = successors[MoveIdx++];

        if (!movePath.empty() && face(movePath.back()) == face(mv))
            continue; // prune same-face sequences

        // avoid cycles along the current path
        if (std::find(searchPath.begin(), searchPath.end(), next) != searchPath.end())
            continue;

        searchPath.push_back(next);
        movePath.push_back(mv);

        Result t = search(searchPath, movePath, g + 1, bound);

        if (t.found) return Result{true, 0};
        if (t.nextThreshold < minNextThreshold)
            minNextThreshold = t.nextThreshold;

        searchPath.pop_back();
        movePath.pop_back();
    }
    return Result{false, minNextThreshold};
}

IDAStar::IDAStar() :
    pdb(PatternDatabase(
            {0,1,2,3,8,9},
            {4,5,6,7,10,11})),
    corner(PDBFileHandler("corner.pdb")),
    edge_start(PDBFileHandler("edge_start.pdb")),
    edge_end(PDBFileHandler("edge_end.pdb"))
{}

bool IDAStar::solve(Cube root, std::vector<Move>& movePath) const{
    std::vector<Cube> searchPath;
    searchPath.push_back(root);
    size_t bound = calculateHeuristic(root);
    while(true) {
        movePath.clear();            // reset for this IDA* iteration
        searchPath.resize(1);        // keep only root

        Result t = search(searchPath, movePath, 0, bound);
        if(t.found) return true;
        if(t.nextThreshold == SIZE_MAX) return false;
        bound = t.nextThreshold;
    }
}