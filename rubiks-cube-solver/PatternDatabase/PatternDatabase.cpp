//
//  PatternDatabase.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#include "PatternDatabase.h"

uint64_t PatternDatabase::factorial(unsigned char n) {
    uint64_t factorial = 1;
    for(uint64_t i = 1; i <= n; i++){
        factorial *= i;
    }
    return factorial;
};

uint64_t PatternDatabase::factoradic(PieceType pieceType, const Cube& cube) {
    unsigned char len = (pieceType == PieceType::Corner) ? 8 : 12;
    uint64_t perm_index = 0;
    uint64_t state = (pieceType == PieceType::Corner) ? cube.getCornerState() : cube.getEdgeState();
    for(unsigned char i = 1; i < len; i++) {
        unsigned char num_larger = 0;
        for(unsigned char j = 0; j < i; j++) {
            if(cube.getState(pieceType, PiecePart::Position, &state, j) > cube.getState(pieceType, PiecePart::Position, &state, i))
               num_larger++;
        }
        perm_index += num_larger * factorial(i);
    }
    return perm_index;
};

uint64_t PatternDatabase::oriBaseEncoding(PieceType pieceType, const Cube& cube) {
    unsigned char base = 0;
    unsigned char len = 0;
    uint64_t state = 0;
    if(pieceType == PieceType::Corner) {
        base = 3;
        len = 8;
        state = cube.getCornerState();
    } else {
        base = 2;
        len = 12;
        state = cube.getEdgeState();
    }
    uint64_t val = 0;
    for(unsigned char i = 0; i < len - 1; i++) {
        val = val * base + cube.getState(pieceType, PiecePart::Orientation, &state, i);
    }
    return val;
};

uint64_t PatternDatabase::encodeState(PieceType pieceType, const Cube& cube) {
    uint64_t numTotalOrientations = 0;
    numTotalOrientations = (pieceType==PieceType::Corner) ? NUM_CORNER_ORIENTATIONS : NUM_EDGE_ORIENTATIONS;
    return factoradic(pieceType, cube) * numTotalOrientations + oriBaseEncoding(pieceType, cube);
};
