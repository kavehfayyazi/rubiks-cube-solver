//
// Created by Kaveh Fayyazi on 8/4/25.
//

#include "IDAStar.h"
#include <cstdint>
#include <algorithm>

size_t IDAStar::calculateHeuristic(const Cube& c) const {
    unsigned char cH = corner.search(pdb.encodeState(PieceType::Corner, c));
    unsigned char e1H = edge_start.search(pdb.encodeState(PieceType::Edge, c, true));
    unsigned char e2H = edge_end.search(pdb.encodeState(PieceType::Edge, c, false));
    return cH + e1H + e2H;
}

// returns false if f (g + h) > bound. calculates f in place
inline bool IDAStar::multiLevelHeuristic(const Cube& c, size_t& f, const size_t& g, const size_t bound) const {
    size_t h = corner.search(pdb.encodeState(PieceType::Corner, c));
    f = g + h; if (f > bound) return false;

    h += edge_start.search(pdb.encodeState(PieceType::Edge, c, true));
    f = g + h; if (f > bound) return false;

    h += edge_end.search(pdb.encodeState(PieceType::Edge, c, false));
    f = g + h; if (f > bound) return false;
    return true;
}

Result IDAStar::search(Cube& cube, std::vector<Move>& movePath, size_t g, size_t bound, Move last) const {
    if (cube.is_solved()) return Result{true, 0};

    size_t f = 0;
    if (!multiLevelHeuristic(cube, f, g, bound)) return Result{false, f};

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
    // write function so

    // while loop so it brings it all the way left,
    // if same face merge and keep going,
    // if opposite face swap
    // other: break

    v.push_back(m);
    if (v.size() == 1) return;

    size_t idx = v.size() - 1; // location of pushed element
    while (idx > 0) { // loop runs while element to left exists
        size_t leftIdx = idx - 1;
        Move L = v[leftIdx];
        Move R = v[idx];

        if (isSameFace(L, R)){ // merge element to left with right
            int t = (getNumTurns(L) + getNumTurns(R)) % 4;
            v.erase(v.begin() + idx); // remove right element

            if (t == 0) {
                v.erase(v.begin() + leftIdx); // remove left element
                return;
            }
            else {
                v[leftIdx] = getMove(face(L), t); // replace element
                idx = leftIdx;
                continue;
            }
        }
        else if (isOpposingFace(L, R)) {
            std::swap(v[leftIdx], v[idx]);
            idx = leftIdx;
            continue;
        }

        break;
    }
}

void IDAStar::condenseMoves(std::vector<Move>& movePath) {
    if (movePath.empty()) return;

    std::vector<Move> moves;
    moves.reserve(movePath.size());

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