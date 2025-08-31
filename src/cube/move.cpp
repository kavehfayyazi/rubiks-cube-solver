//
// Created by Kaveh Fayyazi on 8/27/25.
//

#include "move.h"
#include <string>

const std::array<Move, MOVE_N> MOVES =
    {U,U2,U_PRIME,D,D2,D_PRIME,L,L2,L_PRIME,R,R2,R_PRIME,F,F2,F_PRIME,B,B2,B_PRIME};

const std::array<Move, MOVE_N> INVERSE =
    {U_PRIME,U2,U,D_PRIME,D2,D,L_PRIME,L2,L,R_PRIME,R2,R,F_PRIME,F2,F,B_PRIME,B2,B};

const std::array<std::array<Move, 4>, NUM_FACES> GET_MOVE = {{
/* U */ {MOVE_N, U, U2, U_PRIME},
/* D */ {MOVE_N, D, D2, D_PRIME},
/* L */ {MOVE_N, L, L2, L_PRIME},
/* R */ {MOVE_N, R, R2, R_PRIME},
/* F */ {MOVE_N, F, F2, F_PRIME},
/* B */ {MOVE_N, B, B2, B_PRIME},
}};

const std::array<uint8_t, MOVE_N> GET_TURNS =
    {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3};

const std::array<uint8_t, MOVE_N> FACES =
    {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};

const std::array<uint8_t, MOVE_N> OPPOSING_FACES =
    {1,1,1,0,0,0,3,3,3,2,2,2,5,5,5,4,4,4};

const std::array<std::array<uint8_t, CORNERS_N>, MOVE_N> cp_ = {{
/* U  */ {ULB, URB, URF, ULF, DLF, DRF, DRB, DLB},
/* U2 */ {URB, URF, ULF, ULB, DLF, DRF, DRB, DLB},
/* U' */ {URF, ULF, ULB, URB, DLF, DRF, DRB, DLB},
/* D  */ {ULF, ULB, URB, URF, DRF, DRB, DLB, DLF},
/* D2 */ {ULF, ULB, URB, URF, DRB, DLB, DLF, DRF},
/* D' */ {ULF, ULB, URB, URF, DLB, DLF, DRF, DRB},
/* L  */ {DLF, ULF, URB, URF, DLB, DRF, DRB, ULB},
/* L2 */ {DLB, DLF, URB, URF, ULB, DRF, DRB, ULF},
/* L' */ {ULB, DLB, URB, URF, ULF, DRF, DRB, DLF},
/* R  */ {ULF, ULB, DRB, URB, DLF, URF, DRF, DLB},
/* R2 */ {ULF, ULB, DRF, DRB, DLF, URB, URF, DLB},
/* R' */ {ULF, ULB, URF, DRF, DLF, DRB, URB, DLB},
/* F  */ {URF, ULB, URB, DRF, ULF, DLF, DRB, DLB},
/* F2 */ {DRF, ULB, URB, DLF, URF, ULF, DRB, DLB},
/* F' */ {DLF, ULB, URB, ULF, DRF, URF, DRB, DLB},
/* B  */ {ULF, DLB, ULB, URF, DLF, DRF, URB, DRB},
/* B2 */ {ULF, DRB, DLB, URF, DLF, DRF, ULB, URB},
/* B' */ {ULF, URB, DRB, URF, DLF, DRF, DLB, ULB},
}};

const std::array<std::array<uint8_t, CORNERS_N>, MOVE_N> co_ = {{
/* U  */ {0,0,0,0,0,0,0,0},
/* U2 */ {0,0,0,0,0,0,0,0},
/* U' */ {0,0,0,0,0,0,0,0},
/* D  */ {0,0,0,0,0,0,0,0},
/* D2 */ {0,0,0,0,0,0,0,0},
/* D' */ {0,0,0,0,0,0,0,0},
/* L  */ {1,2,0,0,2,0,0,1},
/* L2 */ {0,0,0,0,0,0,0,0},
/* L' */ {1,2,0,0,2,0,0,1},
/* R  */ {0,0,1,2,0,1,2,0},
/* R2 */ {0,0,0,0,0,0,0,0},
/* R' */ {0,0,1,2,0,1,2,0},
/* F  */ {2,0,0,1,1,2,0,0},
/* F2 */ {0,0,0,0,0,0,0,0},
/* F' */ {2,0,0,1,1,2,0,0},
/* B  */ {0,1,2,0,0,0,1,2},
/* B2 */ {0,0,0,0,0,0,0,0},
/* B' */ {0,1,2,0,0,0,1,2},
}};

const std::array<std::array<uint8_t, EDGES_N>, MOVE_N> ep_ = {{
/* U  */ {UL, UB, UR, UF, DF, DR, DB, DL, LF, RF, RB, LB},
/* U2 */ {UB, UR, UF, UL, DF, DR, DB, DL, LF, RF, RB, LB},
/* U' */ {UR, UF, UL, UB, DF, DR, DB, DL, LF, RF, RB, LB},
/* D  */ {UF, UL, UB, UR, DR, DB, DL, DF, LF, RF, RB, LB},
/* D2 */ {UF, UL, UB, UR, DB, DL, DF, DR, LF, RF, RB, LB},
/* D' */ {UF, UL, UB, UR, DL, DF, DR, DB, LF, RF, RB, LB},
/* L  */ {UF, LF, UB, UR, DF, DR, DB, LB, DL, RF, RB, UL},
/* L2 */ {UF, DL, UB, UR, DF, DR, DB, UL, LB, RF, RB, LF},
/* L' */ {UF, LB, UB, UR, DF, DR, DB, LF, UL, RF, RB, DL},
/* R  */ {UF, UL, UB, RB, DF, RF, DB, DL, LF, UR, DR, LB},
/* R2 */ {UF, UL, UB, DR, DF, UR, DB, DL, LF, RB, RF, LB},
/* R' */ {UF, UL, UB, RF, DF, RB, DB, DL, LF, DR, UR, LB},
/* F  */ {RF, UL, UB, UR, LF, DR, DB, DL, UF, DF, RB, LB},
/* F2 */ {DF, UL, UB, UR, UF, DR, DB, DL, RF, LF, RB, LB},
/* F' */ {LF, UL, UB, UR, RF, DR, DB, DL, DF, UF, RB, LB},
/* B  */ {UF, UL, LB, UR, DF, DR, RB, DL, LF, RF, UB, DB},
/* B2 */ {UF, UL, DB, UR, DF, DR, UB, DL, LF, RF, LB, RB},
/* B' */ {UF, UL, RB, UR, DF, DR, LB, DL, LF, RF, DB, UB},
}};

const std::array<std::array<uint8_t, EDGES_N>, MOVE_N> eo_ = {{
/* U  */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* U2 */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* U' */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* D  */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* D2 */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* D' */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* L  */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* L2 */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* L' */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* R  */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* R2 */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* R' */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* F  */ {1,0,0,0,1,0,0,0,1,1,0,0},
/* F2 */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* F' */ {1,0,0,0,1,0,0,0,1,1,0,0},
/* B  */ {0,0,1,0,0,0,1,0,0,0,1,1},
/* B2 */ {0,0,0,0,0,0,0,0,0,0,0,0},
/* B' */ {0,0,1,0,0,0,1,0,0,0,1,1},
}};

const std::unordered_map<Move, std::string> MOVE_TO_STRING = {
/* U  */ {U,  "U"}, {U2, "U2"}, {U_PRIME, "U'"},
/* D  */ {D,  "D"}, {D2, "D2"}, {D_PRIME, "D'"},
/* L  */ {L,  "L"}, {L2, "L2"}, {L_PRIME, "L'"},
/* R  */ {R,  "R"}, {R2, "R2"}, {R_PRIME, "R'"},
/* F  */ {F,  "F"}, {F2, "F2"}, {F_PRIME, "F'"},
/* B  */ {B,  "B"}, {B2, "B2"}, {B_PRIME, "B'"},
};

uint8_t face(Move a) { return FACES[a]; }
bool isSameFace(Move a, Move b) { return FACES[a] == FACES[b]; }
bool isOpposingFace(Move a, Move b) { return FACES[a] == OPPOSING_FACES[b] || FACES[b] == OPPOSING_FACES[a]; }
uint8_t getNumTurns(Move m) { return GET_TURNS[m]; }
Move getMove(uint8_t f, uint8_t t) { return GET_MOVE[f][t % 4]; }