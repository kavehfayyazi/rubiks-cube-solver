//
// Created by Kaveh Fayyazi on 8/27/25.
//

#include "encode.h"
#include <array>
#include <algorithm>
#include <cstdint>
#include "pdb_constants.h"

// 0! .. 12!
static constexpr uint64_t FACTORIAL[] = {
        1ull,
        1ull,
        2ull,
        6ull,
        24ull,
        120ull,
        720ull,
        5040ull,
        40320ull,
        362880ull,
        3628800ull,
        39916800ull,
        479001600ull
};

// nCr using the table above
const uint64_t C(uint8_t n, uint8_t r) {
    if (n < r) return 0;
    return FACTORIAL[n] / (FACTORIAL[r] * FACTORIAL[n - r]);
}

// -------- Corners (8! * 3^7) --------

// Lehmer code for cp[0..7]
const uint64_t cpNum(const uint8_t cp[8]) {
    uint64_t idx = 0;
    for (int i = 0; i < 8; ++i) {
        int smaller = 0;
        for (int j = i + 1; j < 8; ++j) if (cp[j] < cp[i]) ++smaller;
        idx += smaller * FACTORIAL[7 - i];
    }
    return idx; // 0 .. 8!-1
}

// Base-3 of the first 7 corner orientations
const uint64_t coNum(const uint8_t co[8]) {
    uint64_t val = 0;
    for (int i = 0; i < 7; ++i) val = val * 3ull + (co[i] % 3);
    return val; // 0 .. 3^7 - 1
}

// -------- Edges: half-set (C(12,6) * 6! * 2^6) --------

static inline uint8_t findPosOfPiece(const uint8_t ep[12], uint8_t pieceId) {
    for (uint8_t pos = 0; pos < 12; ++pos) if (ep[pos] == pieceId) return pos;
    return 0xFF; // should never occur
}

// Combination rank of POSITIONS that contain the 6 group pieces
const uint64_t epRank(const uint8_t ep[12], const uint8_t edgeGroup[6]) {
    uint8_t pos[6];
    for (int i = 0; i < 6; ++i) pos[i] = findPosOfPiece(ep, edgeGroup[i]);
    std::sort(pos, pos + 6); // ascending POSITIONS

    uint64_t rank = 0;
    // standard combinadic: sum_{i=0..5} C(pos[i], i+1)
    for (int i = 0; i < 6; ++i) rank += C(pos[i], static_cast<uint8_t>(i + 1));
    return rank; // 0 .. C(12,6)-1
}

// Lehmer code of the 6-permutation within the chosen subset
const uint64_t epNum(const uint8_t ep[12], const uint8_t edgeGroup[6]) {
    // map pieceID -> 0..5 according to edgeGroup order
    uint8_t groupIndex[12]; for (int i = 0; i < 12; ++i) groupIndex[i] = 0xFF;
    for (int i = 0; i < 6;  ++i) groupIndex[edgeGroup[i]] = static_cast<uint8_t>(i);

    // positions of the 6 pieces, ascending
    uint8_t pos[6];
    for (int i = 0; i < 6; ++i) pos[i] = findPosOfPiece(ep, edgeGroup[i]);
    std::sort(pos, pos + 6);

    // sequence in that position-order, expressed as 0..5 labels
    uint8_t perm[6];
    for (int i = 0; i < 6; ++i) perm[i] = groupIndex[ ep[pos[i]] ];

    // Lehmer code
    uint64_t idx = 0;
    for (int i = 0; i < 6; ++i) {
        int smaller = 0;
        for (int j = i + 1; j < 6; ++j) if (perm[j] < perm[i]) ++smaller;
        idx += smaller * FACTORIAL[5 - i];
    }
    return idx; // 0 .. 6!-1
}

// Pack the 6 EO bits in the SAME ascending-POSITION order used above
const uint64_t eoNumHalf(const uint8_t ep[12], const uint8_t eo[12], const uint8_t edgeGroup[6]) {
    uint8_t pos[6];
    for (int i = 0; i < 6; ++i) pos[i] = findPosOfPiece(ep, edgeGroup[i]);
    std::sort(pos, pos + 6);

    uint64_t val = 0;
    for (int i = 0; i < 6; ++i) val = (val << 1) | (eo[pos[i]] & 1);
    return val; // 0 .. 63
}