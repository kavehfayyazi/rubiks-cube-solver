
//
//  cubeTests.cpp
//  Src
//
//  Created by Kaveh Fayyazi on 7/29/25.
//

#include "catch.hpp"
#include "cube.h"

TEST_CASE("Cube default state is solved") {
    Cube cube;
    REQUIRE(cube.is_solved());
}

TEST_CASE("Move inverses are correct") {
    REQUIRE(U == INVERSE[U_PRIME]);
    REQUIRE(U2 == INVERSE[U2]);
    REQUIRE(U_PRIME == INVERSE[U]);
    REQUIRE(D == INVERSE[D_PRIME]);
    REQUIRE(D2 == INVERSE[D2]);
    REQUIRE(D_PRIME == INVERSE[D]);
    REQUIRE(L == INVERSE[L_PRIME]);
    REQUIRE(L2 == INVERSE[L2]);
    REQUIRE(L_PRIME == INVERSE[L]);
    REQUIRE(R == INVERSE[R_PRIME]);
    REQUIRE(R2 == INVERSE[R2]);
    REQUIRE(R_PRIME == INVERSE[R]);
    REQUIRE(F == INVERSE[F_PRIME]);
    REQUIRE(F2 == INVERSE[F2]);
    REQUIRE(F_PRIME == INVERSE[F]);
    REQUIRE(B == INVERSE[B_PRIME]);
    REQUIRE(B2 == INVERSE[B2]);
    REQUIRE(B_PRIME == INVERSE[B]);
}

TEST_CASE("Cube after one turn is not solved and its inverse is solved") {
    Cube cube;
    for (Move m : MOVES) {
        cube.doMove(m);
        REQUIRE_FALSE(cube.is_solved());
        cube.undoMove(m);
        REQUIRE(cube.is_solved());
    }
}

TEST_CASE("Cube after two double turns is solved") {
    Cube cube;
    cube.doMove(U2);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(U2);
    REQUIRE(cube.is_solved());
    cube.doMove(D2);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(D2);
    REQUIRE(cube.is_solved());
    cube.doMove(L2);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(L2);
    REQUIRE(cube.is_solved());
    cube.doMove(R2);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(R2);
    REQUIRE(cube.is_solved());
    cube.doMove(F2);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(F2);
    REQUIRE(cube.is_solved());
    cube.doMove(B2);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(B2);
    REQUIRE(cube.is_solved());
}

TEST_CASE("Cube with each turn for a single face is solved") {
    Cube cube;
    // E.g. U U U2
    cube.doMove(U);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(U);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(U2);
    REQUIRE(cube.is_solved());
    cube.doMove(D);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(D);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(D2);
    REQUIRE(cube.is_solved());
    cube.doMove(L);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(L);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(L2);
    REQUIRE(cube.is_solved());
    cube.doMove(R);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(R);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(R2);
    REQUIRE(cube.is_solved());
    cube.doMove(F);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(F);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(F2);
    REQUIRE(cube.is_solved());
    cube.doMove(B);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(B);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(B2);
    REQUIRE(cube.is_solved());
    // E.g. U' U' U2
    cube.doMove(U_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(U_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(U2);
    REQUIRE(cube.is_solved());
    cube.doMove(D_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(D_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(D2);
    REQUIRE(cube.is_solved());
    cube.doMove(L_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(L_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(L2);
    REQUIRE(cube.is_solved());
    cube.doMove(R_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(R_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(R2);
    REQUIRE(cube.is_solved());
    cube.doMove(F_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(F_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(F2);
    REQUIRE(cube.is_solved());
    cube.doMove(B_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(B_PRIME);
    REQUIRE_FALSE(cube.is_solved());
    cube.doMove(B2);
    REQUIRE(cube.is_solved());
}

TEST_CASE("Cube with random scrabbles and inverses is solved") {
    for (int i = 1; i < 100; ++i) {
        Cube cube;
        auto scramble = cube.genScramble(i);
        for (Move m : scramble) cube.doMove(m);
        REQUIRE_FALSE(cube.is_solved());
        for (auto it = scramble.rbegin(); it != scramble.rend(); ++it) cube.doMove(INVERSE[*it]);
        REQUIRE(cube.is_solved());
    }
}



