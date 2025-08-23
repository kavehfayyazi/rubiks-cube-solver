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
    for (Move m : MOVES) successors.push_back(c.move(MOVE_TO_STRING.at(m)));
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
    for (Move m : MOVES) {
        const Cube &next = successors[MoveIdx++];

        if (!movePath.empty() && face(movePath.back()) == face(m)) continue; // prune same-face sequences

        if (std::find(searchPath.begin(), searchPath.end(), next) != searchPath.end()) continue; // avoid cycles along the current path

        searchPath.push_back(next);
        movePath.push_back(m);

        Result t = search(searchPath, movePath, g + 1, bound);

        if (t.found) return Result{true, 0};
        if (t.nextThreshold < minNextThreshold) minNextThreshold = t.nextThreshold;

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

//inline bool hasReducibleSameFace(const std::vector<Move>& v) {
//    for (size_t i = 1; i < v.size(); ++i) {
//        int fi = face(v[i]);
//        // look left until we hit a non-opposite barrier
//        for (size_t j = i; j > 0; --j) {
//            size_t k = j - 1;
//            if (face(v[k]) == fi) return true;
//            if (!isOpposingFace(v[i], v[k])) break;
//        }
//    }
//    return false;
//}

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
        const auto t = getNumTurns(v[idx]) + getNumTurns(v[idx - 1]);

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
    std::vector<Cube> searchPath;
    searchPath.push_back(root);
    size_t bound = calculateHeuristic(root);
    while (true) {
        movePath.clear();            // reset for this IDA* iteration
        searchPath.resize(1);        // keep only root

        Result t = search(searchPath, movePath, 0, bound);
        if (t.found) {
            condenseMoves(movePath);
            return true;
        }
        if (t.nextThreshold == SIZE_MAX) return false;
        bound = t.nextThreshold;
    }
}