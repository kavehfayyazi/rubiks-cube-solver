//
//  bitUtils.h
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/28/25.
//

#ifndef BITUTILS_H
#define BITUTILS_H

#include <iostream>

void printBits(uint64_t val) {
    for (int i = 63; i >= 0; --i) {
        std::cout << ((val >> i) & 1);
    }
    std::cout << "\n";
}

#endif
