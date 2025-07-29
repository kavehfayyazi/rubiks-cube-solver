//
//  Cube.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/25/25.
//

#include "Cube.h"
#include "bitUtils.h"
#include <string>
#include <stdexcept>

void Cube::switch_pieces(PieceType pieceType, PiecePart piecePart, uint64_t* state, std::array<unsigned char, 4> idxList, unsigned char rot) const {
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

void Cube::orient_corners(uint64_t* state, Move move) const {
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

void Cube::orient_edges(uint64_t* state, Move move) const {
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

Cube::Cube()
: cornerState([&] {
    uint64_t cornerState = 0;
    for(size_t i = 0; i < NUM_CORNERS; i++){
        cornerState |= (uint64_t)i << (CORNER_ORI_BITS * NUM_CORNERS + CORNER_POS_BITS * i);
    }
    return cornerState;
}()),
edgeState([&] {
    uint64_t edgeState = 0;
    for(size_t i = 0; i < NUM_EDGES; i++){
        edgeState |= (uint64_t)i << (EDGE_ORI_BITS * NUM_EDGES + EDGE_POS_BITS * i);
    }
    return edgeState;
}())
{}


Cube::Cube(uint64_t cornerState, uint64_t edgeState)
: cornerState(cornerState) , edgeState(edgeState) {}

uint64_t Cube::getCornerState() const { return cornerState; }

uint64_t Cube::getEdgeState() const { return edgeState; }

unsigned char Cube::getState(PieceType pieceType, PiecePart piecePart, const uint64_t* state, unsigned char idx) const {
    switch(pieceType) {
        case PieceType::Corner:
            switch(piecePart){
                case PiecePart::Position:       return (*state >> (TOTAL_CORNER_ORI_BITS + idx * CORNER_POS_BITS)) & 0b111;
                case PiecePart::Orientation:    return (*state >> (idx * CORNER_ORI_BITS)) & 0b11;
            }
        case PieceType::Edge:
            switch(piecePart){
                case PiecePart::Position:       return (*state >> (TOTAL_EDGE_ORI_BITS + idx * EDGE_POS_BITS)) & 0b1111;
                case PiecePart::Orientation:    return (*state >> (idx * EDGE_ORI_BITS)) & 0b1;
            }
    }
    throw std::invalid_argument("Invalid PieceType or PiecePart.");
}

void Cube::setState(PieceType pieceType, PiecePart piecePart, uint64_t* state, unsigned char idx, unsigned char value) const {
    size_t bit_pos;
    switch(pieceType) {
        case PieceType::Corner:
            switch(piecePart){
                case PiecePart::Position:       bit_pos = TOTAL_CORNER_ORI_BITS + idx * CORNER_POS_BITS;    break;
                case PiecePart::Orientation:    bit_pos = idx * CORNER_POS_BITS;                            break;
            }
            break;
        case PieceType::Edge:
            switch(piecePart){
                case PiecePart::Position:       bit_pos = TOTAL_EDGE_ORI_BITS + idx * EDGE_POS_BITS;        break;
                case PiecePart::Orientation:    bit_pos = idx * EDGE_ORI_BITS;                              break;
            }
    }
    *state &= ~(uint64_t(0b111) << bit_pos);
    *state |= (uint64_t(value & 0b111) << bit_pos);
}

Cube Cube::move(Move move) const {
    unsigned char num_rot = 0;
    
    if(static_cast<int>(move) % 3 == 0) {num_rot = 1;}
    else if(static_cast<int>(move) % 3 == 1) {num_rot = 2;}
    else {num_rot = 3;} // (static_cast<int>(move) % 3 == 2)
    
    uint64_t newCornerState = getCornerState();
    uint64_t newEdgeState = getEdgeState();
    
    // Permute corner and edge pieces (pos + ori)
    switch_pieces(PieceType::Corner, PiecePart::Position, &newCornerState, CORNER_POS_PERMED.at(move), num_rot);
    switch_pieces(PieceType::Corner, PiecePart::Orientation, &newCornerState, CORNER_POS_PERMED.at(move), num_rot);
    switch_pieces(PieceType::Edge, PiecePart::Position, &newEdgeState, EDGE_POS_PERMED.at(move), num_rot);
    switch_pieces(PieceType::Edge, PiecePart::Orientation, &newEdgeState, EDGE_POS_PERMED.at(move), num_rot);
    
    // Orient
    orient_corners(&newCornerState, move);
    orient_edges(&newEdgeState, move);
    
    return Cube(newCornerState, newEdgeState);
}

// Corner i (pos, ori) = x, y
void Cube::printCornerState(const uint64_t* state) const {
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
void Cube::printEdgeState(const uint64_t* state) const {
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

void Cube::printState() const{
    printCornerState(&cornerState);
    printEdgeState(&edgeState);
}

bool Cube::operator==(const Cube& other) const {
    return
        Cube::getCornerState() == other.getCornerState() &&
    Cube::getEdgeState() == other.getEdgeState();
}
