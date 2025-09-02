//
// Created by Kaveh Fayyazi on 8/29/25.
//

#ifndef RUBIKSCUBESOLVER_MAXDEPTHS_API_H
#define RUBIKSCUBESOLVER_MAXDEPTHS_API_H

#include <cstdint>
#include <string>

void printMaxDepth(const std::string& start, bool isCorner=true, bool isEdgeFirst=true);
void printMaxDepths();

#endif //RUBIKSCUBESOLVER_MAXDEPTHS_API_H
