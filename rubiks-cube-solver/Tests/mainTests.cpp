
//
//  mainTests.cpp
//  rubiks-cube-solver
//
//  Created by Kaveh Fayyazi on 7/29/25.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Cube.h"

TEST_CASE("Cube default state is solved") {
    Cube cube;
    REQUIRE(cube.is_solved());
}

TEST_CASE("Cube after one turn is not solved") {
    Cube cube;
    REQUIRE(!cube.move("U").is_solved());
    REQUIRE(!cube.move("U").is_solved());
    REQUIRE(!cube.move("U2").is_solved());
    REQUIRE(!cube.move("D").is_solved());
    REQUIRE(!cube.move("D").is_solved());
    REQUIRE(!cube.move("D2").is_solved());
    REQUIRE(!cube.move("L").is_solved());
    REQUIRE(!cube.move("L").is_solved());
    REQUIRE(!cube.move("L2").is_solved());
    REQUIRE(!cube.move("R").is_solved());
    REQUIRE(!cube.move("R").is_solved());
    REQUIRE(!cube.move("R2").is_solved());
    REQUIRE(!cube.move("F").is_solved());
    REQUIRE(!cube.move("F").is_solved());
    REQUIRE(!cube.move("F2").is_solved());
    REQUIRE(!cube.move("B").is_solved());
    REQUIRE(!cube.move("B").is_solved());
    REQUIRE(!cube.move("B2").is_solved());
}

TEST_CASE("Cube after one turn and its inverse is solved") {
    Cube cube;
    REQUIRE(cube.move("U' U").is_solved());
    REQUIRE(cube.move("U' U").is_solved());
    REQUIRE(cube.move("D' D").is_solved());
    REQUIRE(cube.move("D' D").is_solved());
    REQUIRE(cube.move("L' L").is_solved());
    REQUIRE(cube.move("L' L").is_solved());
    REQUIRE(cube.move("R' R").is_solved());
    REQUIRE(cube.move("R' R").is_solved());
    REQUIRE(cube.move("F' F").is_solved());
    REQUIRE(cube.move("F' F").is_solved());
    REQUIRE(cube.move("B' B").is_solved());
    REQUIRE(cube.move("B' B").is_solved());
}

TEST_CASE("Cube after two double turns is solved") {
    Cube cube;
    REQUIRE(cube.move("U2 U2").is_solved());
    REQUIRE(cube.move("D2 D2").is_solved());
    REQUIRE(cube.move("L2 L2").is_solved());
    REQUIRE(cube.move("R2 R2").is_solved());
    REQUIRE(cube.move("F2 F2").is_solved());
    REQUIRE(cube.move("B2 B2").is_solved());
}

TEST_CASE("Cube with each turn for a single face is solved") {
    Cube cube;
    REQUIRE(cube.move("U U U2").is_solved());
    REQUIRE(cube.move("U U U2").is_solved());
    REQUIRE(cube.move("D D D2").is_solved());
    REQUIRE(cube.move("D D D2").is_solved());
    REQUIRE(cube.move("L L L2").is_solved());
    REQUIRE(cube.move("L L L2").is_solved());
    REQUIRE(cube.move("R R R2").is_solved());
    REQUIRE(cube.move("R R R2").is_solved());
    REQUIRE(cube.move("F F F2").is_solved());
    REQUIRE(cube.move("F F F2").is_solved());
    REQUIRE(cube.move("B B B2").is_solved());
    REQUIRE(cube.move("B B B2").is_solved());

    REQUIRE(cube.move("U' U' U2").is_solved());
    REQUIRE(cube.move("U' U' U2").is_solved());
    REQUIRE(cube.move("D' D' D2").is_solved());
    REQUIRE(cube.move("D' D' D2").is_solved());
    REQUIRE(cube.move("L' L' L2").is_solved());
    REQUIRE(cube.move("L' L' L2").is_solved());
    REQUIRE(cube.move("R' R' R2").is_solved());
    REQUIRE(cube.move("R' R' R2").is_solved());
    REQUIRE(cube.move("F' F' F2").is_solved());
    REQUIRE(cube.move("F' F' F2").is_solved());
    REQUIRE(cube.move("B' B' B2").is_solved());
    REQUIRE(cube.move("B' B' B2").is_solved());

    REQUIRE(cube.move("U U' U' U U2 U2").is_solved());
    REQUIRE(cube.move("U U' U' U U2 U2").is_solved());
    REQUIRE(cube.move("D D' D' D D2 D2").is_solved());
    REQUIRE(cube.move("D D' D' D D2 D2").is_solved());
    REQUIRE(cube.move("L L' L' L L2 L2").is_solved());
    REQUIRE(cube.move("L L' L' L L2 L2").is_solved());
    REQUIRE(cube.move("R R' R' R R2 R2").is_solved());
    REQUIRE(cube.move("R R' R' R R2 R2").is_solved());
    REQUIRE(cube.move("F F' F' F F2 F2").is_solved());
    REQUIRE(cube.move("F F' F' F F2 F2").is_solved());
    REQUIRE(cube.move("B B' B' B B2 B2").is_solved());
    REQUIRE(cube.move("B B' B' B B2 B2").is_solved());
}

