//
//  PatternDatabase.cpp
//  src
//
//  Created by Kaveh Fayyazi on 7/30/25.
//

#ifndef RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H

#include <cstddef>
#include <vector>
#include <optional>
#include <atomic>
#include <array>
#include <cstdint>
#include "Cube.h"

class PatternDatabase {
private:
    void generatePDB(std::string fileName, bool forCorners=true, bool forFirstEdges=true) const;

public:
    void mainPDB();

private:
    inline static std::atomic<size_t> visited;
};

#endif