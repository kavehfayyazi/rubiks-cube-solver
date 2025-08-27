//
// Created by Kaveh Fayyazi on 8/24/25.
//

#ifndef RUBIKSCUBESOLVER_UTILS_H
#define RUBIKSCUBESOLVER_UTILS_H

#include "types.h"
#include <algorithm>

inline constexpr uint8_t face(Move m){ return FACES[static_cast<uint8_t>(m)]; }
inline constexpr uint8_t opposingFace(Move m){ return OPPOSING_FACES[static_cast<uint8_t>(m)]; }
inline constexpr bool isSameFace(Move a, Move b) { return face(a) == face(b); }
inline constexpr bool isOpposingFace(Move a, Move b) { return face(a) == opposingFace(b) || opposingFace(a) == face(b); }

inline constexpr uint8_t getNumTurns(Move m) { return (static_cast<uint8_t>(m) % 3) + 1; }
inline constexpr Move getMove(uint8_t f, uint8_t t) { t = ((t + 4) % 4 ); return (t == 0) ? MOVE_N : static_cast<Move>(f*3 + (t-1)); }

inline constexpr Move inverse(Move m) { uint8_t t = getNumTurns(m); return (t == 2) ? m : getMove(face(m), (t + 2) % 4); }
inline constexpr Move baseOf(Move m) { return static_cast<Move>(face(m) * 3); } // get face (U,D,L,R,F,B)

// Combination
inline constexpr uint64_t C(uint8_t n, uint8_t r) { if (n < r) return 0; return FACTORIAL[n] / (FACTORIAL[r] * FACTORIAL[n-r]); }

// Lehmers code
inline uint64_t cpNum(const uint8_t cp[CORNERS_N]) {
    uint64_t perm_index = 0;
    for (int i = 1; i < CORNERS_N; ++i) {
        uint8_t num_larger = 0;
        uint8_t right = cp[i];
        for (int j = 0; j < i; ++j) {
            uint8_t left = cp[j];
            if (left > right) num_larger++;
        }
        perm_index += num_larger * FACTORIAL[i];
    }
    return perm_index;
}

// Lehmers code
inline uint64_t epNum(const uint8_t ep[12], const uint8_t edgeGroup[6]) {
    uint64_t perm_index = 0;
    for (int i = 1; i < HALF_EDGES_N; ++i) {
        uint8_t num_larger = 0;
        uint8_t right = ep[edgeGroup[i]];
        for (int j = 0; j < i; ++j) {
            uint8_t left = ep[edgeGroup[j]];
            if (left > right) ++num_larger;
        }
        perm_index += num_larger * FACTORIAL[i];
    }
    return perm_index;
}

// uses combinatorial number system ranking
inline uint64_t epRank(const uint8_t ep[12], const uint8_t edgeGroup[6]) {
    uint8_t pos[HALF_EDGES_N]{};
    for (int i = 0; i < HALF_EDGES_N; ++i) pos[i] = ep[edgeGroup[i]];
    std::sort(pos, pos + HALF_EDGES_N);

    uint64_t rank = 0;
    for (int i = 0; i < HALF_EDGES_N; ++i) rank += C(pos[i], i + 1);
    return rank;
}

// base 3 encoding
inline uint64_t coNum(const uint8_t co[8]) {
    uint64_t val = 0;
    for (int i = 0; i < CORNERS_N - 1; ++i) val = val * 3 + co[i];
    return val;
}

// base 2 encoding
inline uint64_t eoNumHalf(const uint8_t eo[EDGES_N], const uint8_t group[HALF_EDGES_N]) {
    uint64_t val = 0;
    for (int i = 0; i < HALF_EDGES_N; ++i) val = (val << 1) | eo[group[i]];
    return val; // 0..63
}

#endif //RUBIKSCUBESOLVER_UTILS_H
