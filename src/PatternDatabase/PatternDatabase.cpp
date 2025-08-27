//
//  PatternDatabase.cpp
//  src
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#include "PatternDatabase.h"
#include "PDBFileHandler.h"
#include <stdexcept>
#include <iostream>
#include <queue>
#include <thread>
#include <unordered_set>
#include "utils.h"

void PatternDatabase::generatePDB(std::string fileName, bool forCorners, bool forFirstEdges) const {
    PDBFileHandler pdb = PDBFileHandler(fileName);

    uint64_t len = (forCorners) ? CORNER_PDB_BYTES : EDGE_PDB_BYTES;
    std::vector<uint8_t> data(len, 0xFF);

    // Piece group to encode
    uint64_t (Cube::*encodeFuncPtr)() const =
        (forCorners) ? &Cube::encodeCorners
                    : (forFirstEdges) ? &Cube::encodeFirstEdges : &Cube::encodeSecondEdges;

    struct Node { Cube c; uint8_t d; Move last; };
    std::queue<Node> q;
    q.push({Cube(), 0, MOVE_N});

    // mark start
    PDBFileHandler::setVal(data, (q.front().c.*encodeFuncPtr)(), 0);

    while (!q.empty()) {
        Node curr = q.front(); q.pop();
        ++visited;
        if (visited % 1000000 == 0) std::cout << visited << " states visited...\n";

        for (Move m : MOVES) {
            if (curr.last != MOVE_N && isSameFace(curr.last, m)) continue;
            curr.c.doMove(m);
            uint64_t idx = (curr.c.*encodeFuncPtr)();

            if (PDBFileHandler::notReached(data, idx)) {
                uint8_t nextDepth = curr.d + 1;
                PDBFileHandler::setVal(data, idx, nextDepth);
                q.push({curr.c, nextDepth, m});        // copy the moved state into the queue
            }
            curr.c.undoMove(m);
        }
    }

    pdb.save(data);
}
//
//unsigned char findMaxDepth(PieceType pieceType, bool isFirstEdgeGroup) const {
//    Cube solved = Cube();
//    std::queue<std::pair<Cube, unsigned char>> q;
//    std::unordered_set<uint64_t> visitedStates;
//    q.emplace(solved, 0);
//    visitedStates.insert(encodeState(pieceType, solved, isFirstEdgeGroup));
//
//    unsigned char maxDepthFound = 0;
//
//    while (!q.empty()) {
//        auto [cube, depth] = q.front();
//        q.pop();
//        if (depth > maxDepthFound) {
//            maxDepthFound = depth;
//        }
//        for (auto& it : STRING_TO_MOVE) {
////            Cube nextCube = cube.move(it.first);
//            Cube nextCube;
//            uint64_t idx = encodeState(pieceType, nextCube, isFirstEdgeGroup);
//            if (visitedStates.insert(idx).second) {
//                q.push({nextCube, depth + 1});
//            }
//        }
//    }
//    return maxDepthFound;
//}
//
//void findMaxDepths() const {
////    std::cout << "Corner max depth: " << (int)findMaxDepth(PieceType::Corner, true) << std::endl;
//    std::cout << "Edge first max depth: " << (int)findMaxDepth(PieceType::Edge, true) << std::endl;
//    std::cout << "Edge second max depth: " << (int)findMaxDepth(PieceType::Edge, false) << std::endl;
//}

void PatternDatabase::mainPDB() {
    std::vector<uint8_t> cornerPDB(     CORNER_PDB_BYTES, 0xFF);
    std::vector<uint8_t> startEdgePDB(  EDGE_PDB_BYTES  , 0xFF);
    std::vector<uint8_t> endEdgePDB(    EDGE_PDB_BYTES  , 0xFF);
    std::thread corner([&]() {      generatePDB("corner.pdb"); });
    std::thread edgeFirst([&]() {   generatePDB("edgeFirst.pdb", false, true); });
    std::thread edgeSecond([&]() {  generatePDB("edgeSecond.pdb", false, false); });
    corner.join();
    edgeFirst.join();
    edgeSecond.join();
}