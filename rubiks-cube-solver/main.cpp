//////
//////  main.cpp
//////  rubiks-cube-solver
//////
//////  Created by Kaveh Fayyazi on 7/25/25.
//////
////
////#include "Cube.h"
////#include <string>
////
////int main(int argc, const char * argv[]) {
////    Cube c = Cube();
////    c.printState();
////    Cube c1 = c.move("U'");
////    c1.printState();
//////    Cube c1 = c.move(Move::U);
//////    printBits(c1.getCornerState());
//////    printBits(c1.getEdgeState());
////}
//
//
//
//
////
////  CubeTests.cpp
////  rubiks-cube-solver
////
////  Created by Kaveh Fayyazi on 7/29/25.
////
//
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//
//#include "Cube.h"
//
//TEST_CASE("Cube default state is solved") {
//    Cube cube;
//    REQUIRE(cube.is_solved());
//}
//
//TEST_CASE("Cube after one turn is not solved") {
//    Cube cube;
//    REQUIRE(!cube.move("U").is_solved());
//    REQUIRE(!cube.move("U").is_solved());
//    REQUIRE(!cube.move("U2").is_solved());
//    REQUIRE(!cube.move("D").is_solved());
//    REQUIRE(!cube.move("D").is_solved());
//    REQUIRE(!cube.move("D2").is_solved());
//    REQUIRE(!cube.move("L").is_solved());
//    REQUIRE(!cube.move("L").is_solved());
//    REQUIRE(!cube.move("L2").is_solved());
//    REQUIRE(!cube.move("R").is_solved());
//    REQUIRE(!cube.move("R").is_solved());
//    REQUIRE(!cube.move("R2").is_solved());
//    REQUIRE(!cube.move("F").is_solved());
//    REQUIRE(!cube.move("F").is_solved());
//    REQUIRE(!cube.move("F2").is_solved());
//    REQUIRE(!cube.move("B").is_solved());
//    REQUIRE(!cube.move("B").is_solved());
//    REQUIRE(!cube.move("B2").is_solved());
//}
//
//TEST_CASE("Cube after one turn and its inverse is solved") {
//    Cube cube;
//    REQUIRE(cube.move("U' U").is_solved());
//    REQUIRE(cube.move("U' U").is_solved());
//    REQUIRE(cube.move("D' D").is_solved());
//    REQUIRE(cube.move("D' D").is_solved());
//    REQUIRE(cube.move("L' L").is_solved());
//    REQUIRE(cube.move("L' L").is_solved());
//    REQUIRE(cube.move("R' R").is_solved());
//    REQUIRE(cube.move("R' R").is_solved());
//    REQUIRE(cube.move("F' F").is_solved());
//    REQUIRE(cube.move("F' F").is_solved());
//    REQUIRE(cube.move("B' B").is_solved());
//    REQUIRE(cube.move("B' B").is_solved());
//}
//
//TEST_CASE("Cube after two double turns is solved") {
//    Cube cube;
//    REQUIRE(cube.move("U2 U2").is_solved());
//    REQUIRE(cube.move("D2 D2").is_solved());
//    REQUIRE(cube.move("L2 L2").is_solved());
//    REQUIRE(cube.move("R2 R2").is_solved());
//    REQUIRE(cube.move("F2 F2").is_solved());
//    REQUIRE(cube.move("B2 B2").is_solved());
//}
//
//TEST_CASE("Cube with each turn for a single face is solved") {
//    Cube cube;
//    REQUIRE(cube.move("U U U2").is_solved());
//    REQUIRE(cube.move("U U U2").is_solved());
//    REQUIRE(cube.move("D D D2").is_solved());
//    REQUIRE(cube.move("D D D2").is_solved());
//    REQUIRE(cube.move("L L L2").is_solved());
//    REQUIRE(cube.move("L L L2").is_solved());
//    REQUIRE(cube.move("R R R2").is_solved());
//    REQUIRE(cube.move("R R R2").is_solved());
//    REQUIRE(cube.move("F F F2").is_solved());
//    REQUIRE(cube.move("F F F2").is_solved());
//    REQUIRE(cube.move("B B B2").is_solved());
//    REQUIRE(cube.move("B B B2").is_solved());
//    
//    REQUIRE(cube.move("U' U' U2").is_solved());
//    REQUIRE(cube.move("U' U' U2").is_solved());
//    REQUIRE(cube.move("D' D' D2").is_solved());
//    REQUIRE(cube.move("D' D' D2").is_solved());
//    REQUIRE(cube.move("L' L' L2").is_solved());
//    REQUIRE(cube.move("L' L' L2").is_solved());
//    REQUIRE(cube.move("R' R' R2").is_solved());
//    REQUIRE(cube.move("R' R' R2").is_solved());
//    REQUIRE(cube.move("F' F' F2").is_solved());
//    REQUIRE(cube.move("F' F' F2").is_solved());
//    REQUIRE(cube.move("B' B' B2").is_solved());
//    REQUIRE(cube.move("B' B' B2").is_solved());
//    
//    REQUIRE(cube.move("U U' U' U U2 U2").is_solved());
//    REQUIRE(cube.move("U U' U' U U2 U2").is_solved());
//    REQUIRE(cube.move("D D' D' D D2 D2").is_solved());
//    REQUIRE(cube.move("D D' D' D D2 D2").is_solved());
//    REQUIRE(cube.move("L L' L' L L2 L2").is_solved());
//    REQUIRE(cube.move("L L' L' L L2 L2").is_solved());
//    REQUIRE(cube.move("R R' R' R R2 R2").is_solved());
//    REQUIRE(cube.move("R R' R' R R2 R2").is_solved());
//    REQUIRE(cube.move("F F' F' F F2 F2").is_solved());
//    REQUIRE(cube.move("F F' F' F F2 F2").is_solved());
//    REQUIRE(cube.move("B B' B' B B2 B2").is_solved());
//    REQUIRE(cube.move("B B' B' B B2 B2").is_solved());
//}

//
//#include "PatternDatabase/PatternDatabase.h"
//
//int main() {
//    PatternDatabase pdb;
//    pdb.mainPDB();
//}

#include <fstream>
#include <iostream>

//// testing write files.
//int main() {
//    std::ofstream file;
//
//    file.open("sample.txt", std::ios::out | std::ios::binary | std::ios::trunc);
//    if(file.is_open()){
//        std::vector<uint8_t> test(88179840/2, 0xFF);
////        char* ctest = "fdsHEHEHEA";
//        file.write(reinterpret_cast<const char*>(test.data()), test.size());
//
////        file << ctest;
////        for (uint8_t c: test){
////            file << c;
////        }
//    }
//    else {
//        std::cerr << "File could not be opened." << std::endl;
//    }
//}

// testing read files

//int main() {
//    std::ifstream file;
//    file.open("sample.txt", std::ios::in | std::ios::binary);
//    if(!file.is_open()) return 1;
//    file.seekg(0, std::ios::end);
//    long fileSize = file.tellg();
//    file.seekg(0, std::ios::beg);
//
//    std::vector<char> buffer(fileSize);
//    file.read(buffer.data(), fileSize);
//    if(!file) return 2;
//    file.close();
//    for(int i = 0; i < 4; i++)
//    {
//std::cout << (((buffer[i] & 0xF0) >> 4) & 0xF) << (buffer[i] & 0x0F) << std::endl ;
//    }
//    std::cout << std::endl;
//    return 0;
//}

#include "PatternDatabase.h"
#include "PDBFileHandler.h"

//int main() {
//    PatternDatabase pdb;
//    pdb.mainPDB();   // kicks off the three threads and writes out .pdb files
//    return 0;
//}

#include <string>

int main() {
    Cube c = Cube();
    std::cout << c.genScramble(2);
}