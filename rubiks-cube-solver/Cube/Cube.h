//
//  Cube.h
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/25/25.
//

#ifndef CUBE_H
#define CUBE_H

#include "moveTables.h"
#include "pieceClassification.h"
#include <array>
#include <string>
#include <cstdint>
#include <stddef.h>

class Cube {
private:
    const uint64_t cornerState;
    const uint64_t edgeState;
    
    void switch_pieces(PieceType pieceType, PiecePart piecePart, uint64_t* state, std::array<unsigned char, 4> idxList, unsigned char rot) const;
    void orient_corners(uint64_t* state, Move move) const;
    void orient_edges(uint64_t* state, Move move) const;
    
    Cube parseMoves(std::string moves, const uint64_t* cornerState, const uint64_t* edgeState) const;
    void singleMove(Move move, uint64_t* cornerState, uint64_t* edgeState) const;
public:
    Cube(); // Default constructor initalizes solved state
    Cube(uint64_t cornerState, uint64_t edgeState);
    
    uint64_t getCornerState() const;
    uint64_t getEdgeState() const;
    
    unsigned char getState(PieceType pieceType, PiecePart piecePart, const uint64_t* state, unsigned char idx) const;
    void setState(PieceType pieceType, PiecePart piecePart, uint64_t* state, unsigned char idx, unsigned char value) const;
    
    Cube move(std::string moves) const;
    
    void printCornerState(const uint64_t* cornerState) const;
    void printEdgeState(const uint64_t* edgeState) const;
    void printState() const;
    
    bool is_solved() const;
    
    bool operator==(const Cube& other) const;
private:
    static constexpr unsigned char NUM_CORNERS = 8;
    static constexpr unsigned char CORNER_POS_BITS = 3;
    static constexpr unsigned char CORNER_ORI_BITS = 2;
    static constexpr unsigned char TOTAL_CORNER_ORI_BITS = NUM_CORNERS * CORNER_ORI_BITS;
    
    static constexpr unsigned char NUM_EDGES = 12;
    static constexpr unsigned char EDGE_POS_BITS = 4;
    static constexpr unsigned char EDGE_ORI_BITS = 1;
    static constexpr unsigned char TOTAL_EDGE_ORI_BITS = NUM_EDGES * EDGE_ORI_BITS;
};

#endif
