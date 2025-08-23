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

Result IDAStar::search(Cube& cube, std::vector<Move>& movePath, size_t g, size_t bound, Move last) const {
    if (cube.is_solved()) return Result{true, 0};

    size_t h = calculateHeuristic(cube);
    size_t f = g + h;
    if (f > bound) return Result{false, f};

    size_t minNextThreshold = SIZE_MAX;

    for (Move m : MOVES) {
        if (last != MOVE_N)
            if (face(m) == face(last)) continue; // skip same face moves (includes inverse)

        cube.doMove(m);
        movePath.push_back(m);

        Result t = search(cube, movePath, g + 1, bound, m);
        if (t.found) return Result{true, 0};
        minNextThreshold = std::min(minNextThreshold, t.nextThreshold);

        cube.undoMove(m);
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

static inline void pushAndReduce(std::vector<Move>& v, Move m) {
    v.push_back(m);
    if (v.size() == 1) return;

    size_t idx = v.size() - 1; // index of m

    // Bubble across opposing faces
    while (idx > 0 && isOpposingFace(v[idx], v[idx - 1])) {
        std::swap(v[idx], v[idx - 1]);
        --idx;
    }

    // Merge with same-face neighbor
    while (idx > 0 && face(v[idx]) == face(v[idx - 1])) {
        const auto f = face(m);
        const auto t = getNumTurns(v[idx]) + getNumTurns(v[idx - 1]) & 3;

        v.erase(v.begin() + idx);   // drop right one
        --idx;                              // now left one is at idx

        if (t == 0) { // canceled out so remove left
            v.erase(v.begin() + idx);
            return;
        } else { // write merged move in place
            v[idx] = getMove(f, t);

            // after merging, the merged move may commute further left
            while (idx > 0 && isOpposingFace(v[idx], v[idx - 1])) {
                std::swap(v[idx], v[idx - 1]);
                --idx;
            }
        }
    }
}

void IDAStar::condenseMoves(std::vector<Move>& movePath) {
    if (movePath.empty()) return;

    std::vector<Move> moves;    moves.reserve(movePath.size());

    for (Move m : movePath) pushAndReduce(moves, m);
    moves.swap(movePath);
}

bool IDAStar::solve(Cube root, std::vector<Move>& movePath) const {
    size_t bound = calculateHeuristic(root);
    while (true) {
        movePath.clear();            // reset for this IDA* iteration

        Result t = search(root, movePath, 0, bound);
        if (t.found) {
            condenseMoves(movePath);
            return true;
        }
        if (t.nextThreshold == SIZE_MAX) return false;
        bound = t.nextThreshold;
    }
}