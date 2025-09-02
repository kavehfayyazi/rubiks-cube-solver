//
// Created by Kaveh Fayyazi on 8/27/25.
//

#include "maxdepths_api.h"
#include <queue>
#include <unordered_set>
#include <iostream>
#include <thread>
#include "cube.h"
#include "move.h"
#include "pdb_handler.h"
#include "pdb_constants.h"

// Can use PDB handler static helper functions
void printMaxDepth(const std::string& start, bool isCorner, bool isEdgeFirst) {
    using Depth = uint8_t;

    uint64_t len = (isCorner) ? CORNER_PDB_BYTES : EDGE_PDB_BYTES;
    std::vector<uint8_t> visitedStates(len, 0xFF);

    uint64_t (Cube::*encodeFuncPtr)() const =
    (isCorner) ? (&Cube::encodeCorners) :
    (isEdgeFirst) ? (&Cube::encodeFirstEdges) :
    (&Cube::encodeSecondEdges);

    struct Node { Cube c; Depth d; Move last; };
    std::queue<Node> q;
    q.push({Cube(), 0, MOVE_N});

    // mark start
    PdbHandler::setVal(visitedStates, (q.front().c.*encodeFuncPtr)(), 0);

    Depth maxDepth = 0;
    while (!q.empty()) {
        Node curr = q.front(); q.pop();

        for (Move m : MOVES) {
            if (curr.last != MOVE_N && isSameFace(curr.last, m)) continue;
            curr.c.doMove(m);
            uint64_t idx = (curr.c.*encodeFuncPtr)();

            if (PdbHandler::notReached(visitedStates, idx)) {
                Depth nextDepth = curr.d + 1;
                PdbHandler::setVal(visitedStates, idx, nextDepth);
                q.push({curr.c, nextDepth, m});        // copy the moved state into the queue
                maxDepth = std::max(nextDepth, maxDepth);
            }
            curr.c.undoMove(m);
        }
    }
    std::cout << start << (int)maxDepth << '\n';
}

void printMaxDepths() {
    std::thread corner([&]() {      printMaxDepth("Corner max depth: "); });
    std::thread edgeFirst([&]() {   printMaxDepth("Edge first max depth: ", false, true); });
    std::thread edgeSecond([&]() {  printMaxDepth("Edge second max depth: ", false, false); });
    corner.join();
    edgeFirst.join();
    edgeSecond.join();
}