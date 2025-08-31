//
// Created by Kaveh Fayyazi on 8/29/25.
//

#ifndef RUBIKSCUBESOLVER_PDBGEN_API_H
#define RUBIKSCUBESOLVER_PDBGEN_API_H

#include <string>

void pdbgen(std::string fileName, bool forCorners, bool forFirstEdges);
void run_pdbgen();

#endif //RUBIKSCUBESOLVER_PDBGEN_API_H