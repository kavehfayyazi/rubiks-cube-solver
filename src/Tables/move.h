//
//  move.h
//  src
//
//  Created by Kaveh Fayyazi on 7/26/25.
//

#ifndef MOVE_H
#define MOVE_H
#include <unordered_map>
#include <string>
#include <array>
#include <vector>

enum Move : unsigned char {
    U=0, U2=1, U_PRIME=2,
    D=3, D2=4, D_PRIME=5,
    L=6, L2=7, L_PRIME=8,
    R=9, R2=10, R_PRIME=11,
    F=12, F2=13, F_PRIME=14,
    B=15, B2=16, B_PRIME=17,
    MOVE_N=18 // Sentinel value
};

inline auto face = [](Move m) { return static_cast<int>(m) / 3; };
inline bool isOpposingFace(Move a, Move b) { return face(a) != face(b) && face(a) / 2 == face(b) / 2; }

// clockwise turns
inline int getNumTurns(Move m) {
    switch (m) {
        case U:case D:case L:case R:case F:case Move::B:                                return 1;
        case U2:case D2:case L2:case R2:case F2:case B2:                                return 2;
        case U_PRIME:case D_PRIME:case L_PRIME:case R_PRIME:case F_PRIME:case B_PRIME:  return 3;
        default: return 0;
    }
}

inline Move getMove(int f, int turns) {
    int t = ((turns % 4) + 4) % 4; // 0..3
    if (t == 0) return MOVE_N;
    int d = (t == 1) ? 0 : (t == 2) ? 1 : 2; // 1=clockwise, 2=2, 3=prime, comply with enum
    return static_cast<Move>(f * 3 + d);
}

inline Move inverse(Move m) {
    if (getNumTurns(m) == 2) return m;
    const auto t = (getNumTurns(m) + 2) % 4;
    return getMove(face(m), t);
}

static constexpr std::array<Move, MOVE_N> MOVES = {
    U,U2,U_PRIME,
    D,D2,D_PRIME,
    L,L2,L_PRIME,
    R,R2,R_PRIME,
    F,F2,F_PRIME,
    B,B2,B_PRIME,
};


inline const std::unordered_map<std::string, Move> STRING_TO_MOVE {
    {"U",   Move::U},
    {"U2",  Move::U2},
    {"U'",  Move::U_PRIME},
    {"D",   Move::D},
    {"D2",  Move::D2},
    {"D'",  Move::D_PRIME},
    {"L",   Move::L},
    {"L2",  Move::L2},
    {"L'",  Move::L_PRIME},
    {"R",   Move::R},
    {"R2",  Move::R2},
    {"R'",  Move::R_PRIME},
    {"F",   Move::F},
    {"F2",  Move::F2},
    {"F'",  Move::F_PRIME},
    {"B",   Move::B},
    {"B2",  Move::B2},
    {"B'",  Move::B_PRIME},
};

inline const std::unordered_map<Move, std::string> MOVE_TO_STRING {
    {Move::U,       "U"},
    {Move::U2,      "U2"},
    {Move::U_PRIME, "U'"},
    {Move::D,       "D"},
    {Move::D2,      "D2"},
    {Move::D_PRIME, "D'"},
    {Move::L,       "L"},
    {Move::L2,      "L2"},
    {Move::L_PRIME, "L'"},
    {Move::R,       "R"},
    {Move::R2,      "R2"},
    {Move::R_PRIME, "R'"},
    {Move::F,       "F"},
    {Move::F2,      "F2"},
    {Move::F_PRIME, "F'"},
    {Move::B,       "B"},
    {Move::B2,      "B2"},
    {Move::B_PRIME, "B'"},
};

inline const std::unordered_map<int, std::string> CODE_TO_MOVE_STRING {
    {0, "U"},
    {1, "U2"},
    {2, "U'"},
    {3, "D"},
    {4, "D2"},
    {5, "D'"},
    {6, "L"},
    {7, "L2"},
    {8, "L'"},
    {9, "R"},
    {10, "R2"},
    {11, "R'"},
    {12, "F"},
    {13, "F2"},
    {14, "F'"},
    {15, "B"},
    {16, "B2"},
    {17, "B'"},
};

extern const std::unordered_map<Move, std::array<unsigned char, 4>> CORNER_POS_PERMED;

#endif
