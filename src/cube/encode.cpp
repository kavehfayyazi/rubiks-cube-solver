//
// Created by Kaveh Fayyazi on 8/27/25.
//

#include "encode.h"
#include <array>
#include "pdb_constants.h"

static constexpr uint64_t FACTORIAL[] = { 1ull, 1ull, 2ull, 6ull, 24ull, 120ull, 720ull, 5040ull, 40320ull, 362880ull, 3628800ull, 39916800ull, 479001600ull };
// Combination

const uint64_t C(uint8_t n, uint8_t r) { if (n < r) return 0; return FACTORIAL[n] / (FACTORIAL[r] * FACTORIAL[n-r]); }

// Lehmers code
const uint64_t cpNum(const uint8_t cp[8]) {
    uint64_t perm_index = 0;
    for (int i = 1; i < 8; ++i) {
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

// base 3 encoding
const uint64_t coNum(const uint8_t co[8]) {
    uint64_t val = 0;
    for (int i = 0; i < 7; ++i) val = val * 3 + co[i];
    return val;
}

// Lehmers code
const uint64_t epNum(const uint8_t ep[6], const uint8_t edgeGroup[6]) {
    uint64_t perm_index = 0;
    for (int i = 1; i < 6; ++i) {
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
const uint64_t epRank(const uint8_t ep[6], const uint8_t edgeGroup[6]) {
    uint8_t pos[6]{};
    for (int i = 0; i < 6; ++i) pos[i] = ep[edgeGroup[i]];
    std::sort(pos, pos + 6);

    uint64_t rank = 0;
    for (int i = 0; i < 6; ++i) rank += C(pos[i], i + 1);
    return rank;
}

// base 2 encoding
const uint64_t eoNumHalf(const uint8_t eo[6], const uint8_t group[6]) {
    uint64_t val = 0;
    for (int i = 0; i < 6; ++i) val = (val << 1) | eo[group[i]];
    return val; // 0..63
}