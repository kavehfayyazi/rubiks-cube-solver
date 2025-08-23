//
//  Cube.cpp
//  src
//
//  Created by Kaveh Fayyazi on 7/25/25.
//

#include "Cube.h"
#include <algorithm>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <random>

void printBits(uint64_t val) {
    for (int i = 63; i >= 0; --i) {
        std::cout << ((val >> i) & 1);
    }
    std::cout << "\n";
}

void Cube::switch_pieces(PieceType pieceType, PiecePart piecePart, uint64_t& state, std::array<unsigned char, 4> idxList, unsigned char rot) const {
    size_t i;
    unsigned char temp = 0;
    switch(rot) {
        case 1:
            temp = getState(pieceType, piecePart, state, idxList[3]);
            for(i = 3; i > 0; i--) {
                setState(pieceType, piecePart, state, idxList[i], getState(pieceType, piecePart, state, idxList[i-1]));
            }
            setState(pieceType, piecePart, state, idxList[0], temp);
            break;
        case 2:
            // even indices
            temp = getState(pieceType, piecePart, state, idxList[0]);
            setState(pieceType, piecePart, state, idxList[0], getState(pieceType, piecePart, state, idxList[2]));
            setState(pieceType, piecePart, state, idxList[2], temp);
            
            // odd indices
            temp = getState(pieceType, piecePart, state, idxList[1]);
            setState(pieceType, piecePart, state, idxList[1], getState(pieceType, piecePart, state, idxList[3]));
            setState(pieceType, piecePart, state, idxList[3], temp);
            break;
        case 3:
            temp = getState(pieceType, piecePart, state, idxList[0]);
            for(i = 0; i < 3; i++) {
                setState(pieceType, piecePart, state, idxList[i], getState(pieceType, piecePart, state, idxList[i+1]));
            }
            setState(pieceType, piecePart, state, idxList[3], temp);
            break;
    };
};

void Cube::orient_corners(uint64_t& state, Move move) const {
    auto it = CORNER_POS_ORIENTED.find(move);
    if(it != CORNER_POS_ORIENTED.end()) {
        std::array<unsigned char, 4> idxList = CORNER_POS_PERMED.at(move);
        for(size_t i = 0; i < 4; i++) {
            unsigned char ori = getState(PieceType::Corner, PiecePart::Orientation, state, idxList[i]);
            if(i % 2 == 1) {
                setState(PieceType::Corner, PiecePart::Orientation, state, idxList[i], (ori + 1) % 3);
            } else {
                setState(PieceType::Corner, PiecePart::Orientation, state, idxList[i], (ori + 2) % 3);
            }
        }
    };
}

void Cube::orient_edges(uint64_t& state, Move move) const {
    auto it1 = EDGE_POS_ORIENTED.find(move);
    if(it1 != EDGE_POS_ORIENTED.end()) {
        for(size_t i = 0; i < 12; i++) {
            auto it2 = EDGE_POS_PERMED.find(move);
            if(it2 != EDGE_POS_PERMED.end()) {
                bool foundIdxInPerm = std::any_of(EDGE_POS_PERMED.at(move).begin(),EDGE_POS_PERMED.at(move).end(),[&](unsigned char elem) {
                    return elem == i;
                });
                bool foundIdxInOri = std::any_of(EDGE_POS_ORIENTED.at(move).begin(),EDGE_POS_ORIENTED.at(move).end(),[&](unsigned char elem) {
                    return elem == i;
                });
                if(foundIdxInPerm && foundIdxInOri) {
                    unsigned char ori = getState(PieceType::Edge, PiecePart::Orientation, state, i);
                    setState(PieceType::Edge, PiecePart::Orientation, state, i, 1-ori);
                }
            }
        }
    }
}

Cube Cube::parseMoves(std::string moves, const uint64_t& cornerState, const uint64_t& edgeState) const {
    std::stringstream s(moves);
    std::string move;
    uint64_t newCornerState = cornerState;
    uint64_t newEdgeState = edgeState;
    while(s >> move){
        auto it = STRING_TO_MOVE.find(move);
        if(it != STRING_TO_MOVE.end()) singleMove(STRING_TO_MOVE.at(move), newCornerState, newEdgeState);
        else throw std::invalid_argument("Invalid move argument.");
    }
    return Cube(newCornerState, newEdgeState);
}

void Cube::singleMove(Move move, uint64_t& cornerState, uint64_t& edgeState) const {
    unsigned char num_rot = 0;
    
    if(static_cast<int>(move) % 3 == 0) {num_rot = 1;}
    else if(static_cast<int>(move) % 3 == 1) {num_rot = 2;}
    else {num_rot = 3;} // (static_cast<int>(move) % 3 == 2)
    
    // Permute corner and edge pieces (pos + ori)
    switch_pieces(PieceType::Corner, PiecePart::Position, cornerState, CORNER_POS_PERMED.at(move), num_rot);
    switch_pieces(PieceType::Corner, PiecePart::Orientation, cornerState, CORNER_POS_PERMED.at(move), num_rot);
    switch_pieces(PieceType::Edge, PiecePart::Position, edgeState, EDGE_POS_PERMED.at(move), num_rot);
    switch_pieces(PieceType::Edge, PiecePart::Orientation, edgeState, EDGE_POS_PERMED.at(move), num_rot);
    
    // Orient
    orient_corners(cornerState, move);
    orient_edges(edgeState, move);
}

Cube::Cube()
: cornerState([&] {
    uint64_t cornerState = 0;
    for(size_t i = 0; i < NUM_CORNERS; i++){
        cornerState |= (0ULL << (i * CORNER_ORI_BITS));              // orientation
        cornerState |= (uint64_t(i) << (TOTAL_CORNER_ORI_BITS + i * CORNER_POS_BITS));  // position
    }
    return cornerState;
}()),
edgeState([&] {
    uint64_t edgeState = 0;
    for(size_t i = 0; i < NUM_EDGES; i++){
        edgeState |= (0ULL << (i * EDGE_ORI_BITS));              // orientation
        edgeState |= (uint64_t(i) << (TOTAL_EDGE_ORI_BITS + i * EDGE_POS_BITS));  // position
    }
    return edgeState;
}())
{}

Cube::Cube(uint64_t cornerState, uint64_t edgeState) : cornerState(cornerState), edgeState(edgeState) {}


std::vector<Move> Cube::genScramble(int n) const {
    if (n == 0) return std::vector<Move>{};
    std::vector<Move> scramble;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, MOVE_N - 1);

    Move prevMove = MOVE_N;
    for (int i = 0; i < n; i++) {
        Move currMove;
        int move;
        while (true) {
            move = dist(gen);
            currMove = STRING_TO_MOVE.at(CODE_TO_MOVE_STRING.at(move));
            if (face(currMove) != face(prevMove)) break;
        }
        scramble.push_back(currMove);
        prevMove = currMove;
    }
    return scramble;
}

uint64_t Cube::getCornerState() const { return cornerState; }

uint64_t Cube::getEdgeState() const { return edgeState; }

unsigned char Cube::getState(PieceType pieceType, PiecePart piecePart, const uint64_t& state, unsigned char idx) const {
    switch(pieceType) {
        case PieceType::Corner:
            switch(piecePart){
                case PiecePart::Position:       return (state >> (TOTAL_CORNER_ORI_BITS + idx * CORNER_POS_BITS)) & 0b111;
                case PiecePart::Orientation:    return (state >> (idx * CORNER_ORI_BITS)) & 0b11;
            }
        case PieceType::Edge:
            switch(piecePart){
                case PiecePart::Position:       return (state >> (TOTAL_EDGE_ORI_BITS + idx * EDGE_POS_BITS)) & 0b1111;
                case PiecePart::Orientation:    return (state >> (idx * EDGE_ORI_BITS)) & 0b1;
            }
    }
    throw std::invalid_argument("Invalid PieceType or PiecePart.");
}

void Cube::setState(PieceType pieceType, PiecePart piecePart, uint64_t& state, unsigned char idx, unsigned char value) const {
    size_t bit_pos;
    unsigned char num_bits;
    
    switch(pieceType) {
        case PieceType::Corner:
            switch(piecePart){
                case PiecePart::Position:
                    bit_pos = TOTAL_CORNER_ORI_BITS + idx * CORNER_POS_BITS;
                    num_bits = CORNER_POS_BITS;
                    break;
                case PiecePart::Orientation:
                    bit_pos = idx * CORNER_ORI_BITS;
                    num_bits = CORNER_ORI_BITS;
                    break;
            }
            break;
        case PieceType::Edge:
            switch(piecePart){
                case PiecePart::Position:
                    bit_pos = TOTAL_EDGE_ORI_BITS + idx * EDGE_POS_BITS;
                    num_bits = EDGE_POS_BITS;
                    break;
                case PiecePart::Orientation:
                    bit_pos = idx * EDGE_ORI_BITS;
                    num_bits = EDGE_ORI_BITS;
                    break;
            }
    }
    state &= ~((uint64_t((1 << num_bits) - 1)) << bit_pos);
    state |= ((uint64_t(value & ((1 << num_bits) - 1))) << bit_pos);
}

void Cube::doMove(Move move) {
    singleMove(move, cornerState, edgeState);
}

void Cube::undoMove(Move move) {
    singleMove(inverse(move), cornerState, edgeState);
}

void Cube::doMoves(std::vector<Move> moves) {
    for (Move m : moves) singleMove(m, cornerState, edgeState);
}

// Corner i (pos, ori) = x, y
void Cube::printCornerState(const uint64_t& state) const {
    for(size_t i = 0; i < NUM_CORNERS; i++) {
        std::cout
        << "Corner "
        << i << " (pos, ori) = "
        << (int)getState(PieceType::Corner,PiecePart::Position,state,i)
        << ", "
        << (int)getState(PieceType::Corner,PiecePart::Orientation,state,i)
        << "\n";
    }
}

// Edge i (pos, ori) = x, y
void Cube::printEdgeState(const uint64_t& state) const {
    for(size_t i = 0; i < NUM_EDGES; i++) {
        std::string parenSpacing = "   (pos, ori) = ";
        if(i >= 10) parenSpacing = "  (pos, ori) = ";
        
        int pos = (int)getState(PieceType::Edge,PiecePart::Position,state,i);
        int ori = (int)getState(PieceType::Edge,PiecePart::Orientation,state,i);
        
        std::string     commaSpacing = ", ";
        if(pos >= 10)   commaSpacing = ",";
        
        std::cout << "Edge " << i << parenSpacing << pos << commaSpacing << ori << "\n";
    }
}

void Cube::printState() const {
    printCornerState(cornerState);
    printEdgeState(edgeState);
    printBits(this->getCornerState());
    printBits(this->getEdgeState());

}

bool Cube::is_solved() const { return cornerState == solvedCornerState && edgeState == solvedEdgeState; }

bool Cube::operator==(const Cube& other) const {
    return
        Cube::getCornerState() == other.getCornerState() &&
        Cube::getEdgeState() == other.getEdgeState();
}