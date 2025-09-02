//
//  Cube.cpp
//  Src
//
//  Created by Kaveh Fayyazi on 7/25/25.
//

#include "cube.h"
#include <random>
#include "move.h"
#include "encode.h"
#include "pdb_constants.h"
#include "cube_constants.h"

// Solved constructor
Cube::Cube() {
    for (int i=0;i<CORNERS_N;++i){ cp[i]=i; co[i]=0; }
    for (int i=0;i<EDGES_N;  ++i){ ep[i]=i; eo[i]=0; }
}

Cube::Cube(const uint8_t cp[8], const uint8_t co[8], const uint8_t ep[12], const uint8_t eo[12]) {
    std::copy(cp, cp + 8,  this->cp); std::copy(co, co + 8,  this->co);
    std::copy(ep, ep + 12, this->ep); std::copy(eo, eo + 12, this->eo);
}

std::vector<Move> Cube::genScramble(int n) {
    if (n == 0) return std::vector<Move>{};
    std::vector<Move> scramble;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, MOVE_N - 1);

    Move prevPrevMove = MOVE_N;
    Move prevMove = MOVE_N;
    for (int i = 0; i < n; i++) {
        Move currMove;
        int move;
        while (true) {
            move = dist(gen);
            currMove = MOVES[move];

            // Block A B A where B is opposite face of A (e.g., R L R)
            if (prevPrevMove != MOVE_N && prevMove != MOVE_N &&
                isSameFace(currMove, prevPrevMove) && isOpposingFace(currMove, prevMove))
                continue;

            // Block same-face repeats
            if (prevMove != MOVE_N && isSameFace(currMove, prevMove)) continue;

            break; // acceptable
        }
        scramble.push_back(currMove);
        prevPrevMove = prevMove;
        prevMove = currMove;
    }
    return scramble;
}

uint64_t Cube::encodeCorners() const { return cpNum(cp) * NUM_CORNER_ORIENTATIONS + coNum(co); }
uint64_t Cube::encodeFirstEdges() const {
    return
            (epRank(ep, edgesFirstHalf) * NUM_EDGE_PERMUTATIONS + epNum(ep, edgesFirstHalf)) * // permutation numbering
            NUM_EDGE_ORIENTATIONS + eoNumHalf(ep, eo, edgesFirstHalf);
}
uint64_t Cube::encodeSecondEdges() const {
    return
            (epRank(ep, edgesSecondHalf) * NUM_EDGE_PERMUTATIONS + epNum(ep, edgesSecondHalf)) * // permutation numbering
            NUM_EDGE_ORIENTATIONS + eoNumHalf(ep, eo, edgesSecondHalf);
}

void Cube::doMove(Move m) {
    uint8_t ncp[8], nco[8], nep[12], neo[12];

    // map i -> f
    for (int i = 0; i < CORNERS_N; ++i) {
        const uint8_t f = cp_[m][i];
        ncp[f] = cp[i];
        nco[f] = (co[i] + co_[m][f]) % 3;
    }
    for (int i = 0; i < EDGES_N; ++i) {
        const uint8_t f = ep_[m][i];
        nep[f] = ep[i];
        neo[f] = (eo[i] + eo_[m][f]) & 1;
    }

    std::copy(std::begin(ncp), std::end(ncp), cp);
    std::copy(std::begin(nco), std::end(nco), co);
    std::copy(std::begin(nep), std::end(nep), ep);
    std::copy(std::begin(neo), std::end(neo), eo);
}

void Cube::undoMove(Move m) { doMove(INVERSE[m]); }

void Cube::doMoves(const std::vector<Move>& moves) { for (Move m : moves) doMove(m); }

bool Cube::is_solved() const {
    for(int i=0;i<CORNERS_N;++i) if(cp[i]!=CP_SOLVED[i]||co[i]!=CO_SOLVED[i]) return false;
    for(int i=0;i<EDGES_N;  ++i) if(ep[i]!=EP_SOLVED[i]||eo[i]!=EO_SOLVED[i]) return false;
    return true;
}

bool Cube::operator==(const Cube& other) const {
    for(int i=0;i<CORNERS_N;++i) if(cp[i]!=other.cp[i]||co[i]!=other.co[i]) return false;
    for(int i=0;i<EDGES_N;  ++i) if(ep[i]!=other.ep[i]||eo[i]!=other.eo[i]) return false;
    return true;
}