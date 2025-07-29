//
//  move.h
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/26/25.
//

#ifndef MOVE_H
#define MOVE_H

enum Move : unsigned char {
    U=0, U2=1, U_PRIME=2,
    D=3, D2=4, D_PRIME=5,
    L=6, L2=7, L_PRIME=8,
    R=9, R2=10, R_PRIME=11,
    F=12, F2=13, F_PRIME=14,
    B=15, B2=16, B_PRIME=17,
};

#endif
