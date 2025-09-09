//
// Created by Kaveh Fayyazi on 8/4/25.
//

#include "ida_star.h"

static inline uint8_t ceil_div(uint8_t x, uint8_t d) { return (uint8_t)((x + d - 1) / d); }

static inline uint8_t combineH(uint8_t c, uint8_t e1, uint8_t e2) {
    uint8_t h1 = std::max({c, e1, e2});
    uint8_t h2 = std::max(ceil_div((uint8_t)(e1 + e2), 2),
                          std::max(ceil_div((uint8_t)(c + e1), 2),
                                   ceil_div((uint8_t)(c + e2), 2)));
    uint8_t h3 = ceil_div((uint8_t)(c + e1 + e2), 3);
    return std::max(h1, std::max(h2, h3));
}

uint8_t IDAStar::calculateHeuristic(const Cube& c) const {
    unsigned char cH  = corner.getPDBVal(c.encodeCorners());
    unsigned char e1H = edgeStart.getPDBVal(c.encodeFirstEdges());
    unsigned char e2H = edgeEnd.getPDBVal(c.encodeSecondEdges());
    return combineH(cH, e1H, e2H);
}

// returns false if f (g + h) > bound. calculates f in place
bool IDAStar::multiLevelHeuristic(const Cube& c, size_t& f, const size_t& g, const size_t bound) const {
    uint8_t cH  = corner.getPDBVal(c.encodeCorners());
    uint8_t e1H = edgeStart.getPDBVal(c.encodeFirstEdges());
    uint8_t e2H = edgeEnd.getPDBVal(c.encodeSecondEdges());
    size_t h = combineH(cH, e1H, e2H);
    f = g + h;
    return f <= bound;
}

Result IDAStar::search(Cube& cube, std::vector<Move>& movePath, size_t g, size_t bound, Move last, Move last2, std::unordered_map<uint64_t, TTEntry>* tt) const {
    if (cube.is_solved()) return Result{true, 0};

    size_t f = 0;
    if (!multiLevelHeuristic(cube, f, g, bound)) return Result{false, f};

    // full state hash
    auto mix64 = [](uint64_t x){
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    };
    const uint64_t kc = mix64(cube.encodeCorners());
    const uint64_t k1 = mix64(cube.encodeFirstEdges());
    const uint64_t k2 = mix64(cube.encodeSecondEdges());
    uint64_t key = kc ^ (k1 * 0x9e3779b97f4a7c15ULL) ^ (k2 * 0xbf58476d1ce4e5b9ULL);

    auto it = tt->find(key);
    if (it != tt->end() && g >= it->second.best_g) {
        return Result{false, SIZE_MAX}; // dominated: we’ve seen as good or better
    }
    (*tt)[key] = TTEntry{(uint16_t)g};

    size_t minNextThreshold = SIZE_MAX;

    // Build & sort children by heuristic
    struct Child { Move m; uint8_t h; };
    Child kids[18]; int k = 0;

    for (Move m : MOVES) {
        if (last != MOVE_N && isSameFace(m, last)) continue;
        if (last2 != MOVE_N && isSameFace(m, last2) && isOpposingFace(m, last)) continue;

        cube.doMove(m);
        uint8_t hChild = combineH(
                corner.getPDBVal(cube.encodeCorners()),
                edgeStart.getPDBVal(cube.encodeFirstEdges()),
                edgeEnd.getPDBVal(cube.encodeSecondEdges())
        );
        cube.undoMove(m);
        kids[k++] = {m, hChild};
    }

    std::sort(kids, kids + k, [](const Child& a, const Child& b){ return a.h < b.h; });

    for (int i = 0; i < k; ++i) {
        Move m = kids[i].m;
        const size_t child_f = (g + 1) + kids[i].h;   // h is max(C,E1,E2) for the child

        if (child_f > bound) {                        // PRE-PRUNE: don’t recurse
            minNextThreshold = std::min(minNextThreshold, child_f);
            continue;
        }

        cube.doMove(m);
        movePath.push_back(m);
        Result t = search(cube, movePath, g + 1, bound, m, last, tt);
        if (t.found) return Result{true, 0};
        minNextThreshold = std::min(minNextThreshold, t.nextThreshold);
        cube.undoMove(m);
        movePath.pop_back();
    }

    return Result{false, minNextThreshold};
}
#include <iostream>

IDAStar::IDAStar() :
    corner(PdbHandler(PDB_CORNER_FILENAME)),
    edgeStart(PdbHandler(PDB_EDGE_FIRST_FILENAME)),
    edgeEnd(PdbHandler(PDB_EDGE_SECOND_FILENAME))
{
    corner.load();
    edgeStart.load();
    edgeEnd.load();
}

static inline void pushAndReduce(std::vector<Move>& v, Move m) {
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
        movePath.clear(); // reset for this IDA* iteration
        std::unordered_map<uint64_t, TTEntry> tt;
        Result t = search(root, movePath, 0, bound, MOVE_N, MOVE_N, &tt);
        if (t.found) {
            condenseMoves(movePath);
            return true;
        }
        if (t.nextThreshold == SIZE_MAX) return false;
        bound = t.nextThreshold;
    }
}

void IDAStar::solveScramble(int n, MoveList& scramble, MoveList& solve) const {
    scramble.clear(); solve.clear();
    Cube c = Cube();
    scramble = c.genScramble(n);
    c.doMoves(scramble);
    this->solve(c, solve);
    c.doMoves(solve);
    if (!c.is_solved()) throw std::runtime_error("Error with solver.");
}