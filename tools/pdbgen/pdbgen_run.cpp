
#include "pdbgen_api.h"
#include <thread>
#include <iostream>
#include "pdb_handler.h"
#include "pdb_constants.h"
#include "cube.h"

void pdbgen(std::string fileName, bool forCorners, bool forFirstEdges) {
    PdbHandler pdb = PdbHandler(fileName);

    uint64_t len = (forCorners) ? CORNER_PDB_BYTES : EDGE_PDB_BYTES;
    std::vector<uint8_t> data(len, 0xFF);

    // Piece group to encode
    uint64_t (Cube::*encodeFuncPtr)() const =
            (forCorners) ? &Cube::encodeCorners :
            (forFirstEdges) ? &Cube::encodeFirstEdges : &Cube::encodeSecondEdges;

    struct Node { Cube c; uint8_t d; Move last; };
    std::queue<Node> q;
    q.push({Cube(), 0, MOVE_N});

    // mark start
    PdbHandler::setVal(data, (q.front().c.*encodeFuncPtr)(), 0);

    while (!q.empty()) {
        Node curr = q.front(); q.pop();

        for (Move m : MOVES) {
            if (curr.last != MOVE_N && isSameFace(curr.last, m)) continue;
            curr.c.doMove(m);
            uint64_t idx = (curr.c.*encodeFuncPtr)();

            if (PdbHandler::notReached(data, idx)) {
                uint8_t nextDepth = curr.d + 1;
                PdbHandler::setVal(data, idx, nextDepth);
                q.push({curr.c, nextDepth, m});        // copy the moved state into the queue
            }
            curr.c.undoMove(m);
        }
    }

    pdb.save(data);
    std::string pieceGroup = (forCorners) ? "Corners" :
                             (forFirstEdges) ? "First edges" : "Second edges";
    std::cout << pieceGroup << " generated." << '\n';
}

void run_pdbgen() {
    std::thread corner([&]() {      pdbgen(PDB_CORNER_FILENAME); });
    std::thread edgeFirst([&]() {   pdbgen(PDB_EDGE_FIRST_FILENAME, false, true); });
    std::thread edgeSecond([&]() {  pdbgen(PDB_EDGE_SECOND_FILENAME, false, false); });
    corner.join();
    edgeFirst.join();
    edgeSecond.join();
}