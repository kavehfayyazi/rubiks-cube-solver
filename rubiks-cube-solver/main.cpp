//
//  main.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/25/25.
//

#include "Cube.h"

int main(int argc, const char * argv[]) {
    Cube c = Cube();
    c.printState();
    Cube c1 = c.move(Move::U2);
    c1.printState();
//    Cube c1 = c.move(Move::U);
//    printBits(c1.getCornerState());
//    printBits(c1.getEdgeState());
}
