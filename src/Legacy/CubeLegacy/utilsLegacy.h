//
// Created by Kaveh Fayyazi on 8/24/25.
//

#ifndef RUBIKSCUBESOLVER_UTILS_H
#define RUBIKSCUBESOLVER_UTILS_H

#include "typesLegacy.h"

inline constexpr uint8_t face(Move m){ return FACES[static_cast<uint8_t>(m)]; }
inline constexpr uint8_t opposingFace(Move m){ return OPPOSING_FACES[static_cast<uint8_t>(m)]; }
inline constexpr bool isSameFace(Move a, Move b) { return face(a) == face(b); }
inline constexpr bool isOpposingFace(Move a, Move b) { return face(a) == opposingFace(b) || opposingFace(a) == face(b); }

inline constexpr uint8_t getNumTurns(Move m) { return (static_cast<uint8_t>(m) % 3) + 1; }
inline constexpr Move getMove(uint8_t f, uint8_t t) { t = ((t + 4) % 4 ); return (t == 0) ? MOVE_N : static_cast<Move>(t); }

inline constexpr Move inverse(Move m) { uint8_t t = getNumTurns(m); return (t == 2) ? m : getMove(face(m), (t + 2) % 4); }
inline constexpr Move baseOf(Move m) { return static_cast<Move>(face(m) * 3); } // get face (U,D,L,R,F,B)

#endif //RUBIKSCUBESOLVER_UTILS_H
