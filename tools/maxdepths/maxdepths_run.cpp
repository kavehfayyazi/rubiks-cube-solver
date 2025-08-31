//
// Created by Kaveh Fayyazi on 8/27/25.
//

#include "maxdepths_api.h"
#include <queue>
#include <unordered_set>
#include <iostream>
#include "cube.h"
#include "move.h"

uint8_t findMaxDepth(bool isCorner, bool isEdgeFirst) {
    using Depth = uint8_t;

    uint64_t (Cube::*encodeFuncPtr)() const =
        (isCorner) ? (&Cube::encodeCorners) :
        (isEdgeFirst) ? (&Cube::encodeFirstEdges) :
                        (&Cube::encodeSecondEdges);

    std::queue<std::pair<Cube, Depth>> q;
    std::unordered_set<uint64_t> visitedStates;

    Cube start{};
    visitedStates.insert((start.*encodeFuncPtr)());
    q.emplace(start, 0);

    Depth maxDepthFound = 0;

    while (!q.empty()) {
        auto [curr, depth] = q.front();
        q.pop();

        if (depth > maxDepthFound) maxDepthFound = depth;

        for (Move m : MOVES) {
            Cube next = curr;
            next.doMove(m);

            uint64_t code = (next.*encodeFuncPtr)();
            if (visitedStates.insert(code).second) q.emplace(next, depth + 1);
        }
    }
    return maxDepthFound;
}

void printMaxDepths() {
    std::cout << "Corner max depth: "       << (int)findMaxDepth()              << '\n';
    std::cout << "Edge first max depth: "   << (int)findMaxDepth(false, true)   << '\n';
    std::cout << "Edge second max depth: "  << (int)findMaxDepth(false, false)  << std::endl;
}