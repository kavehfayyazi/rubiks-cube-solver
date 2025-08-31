//
// Created by Kaveh Fayyazi on 8/27/25.
//

#ifndef RUBIKSCUBESOLVER_ENCODE_H
#define RUBIKSCUBESOLVER_ENCODE_H

#include <cstdint>

// Combination
extern const uint64_t C(uint8_t n, uint8_t r);

// Lehmers code
extern const uint64_t cpNum(const uint8_t cp[8]);

// base 3 encoding
extern const uint64_t coNum(const uint8_t co[8]);

// Lehmers code
extern const uint64_t epNum(const uint8_t ep[12], const uint8_t edgeGroup[6]);

// uses combinatorial number system ranking
extern const uint64_t epRank(const uint8_t ep[12], const uint8_t edgeGroup[6]);

// base 2 encoding
extern const uint64_t eoNumHalf(const uint8_t eo[12], const uint8_t group[6]);

#endif //RUBIKSCUBESOLVER_ENCODE_H
