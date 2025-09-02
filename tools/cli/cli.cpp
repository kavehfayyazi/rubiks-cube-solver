#include <iostream>
#include <sstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <string>
#include "move.h"
#include "cube.h"
#include "maxdepths_api.h"
#include "pdbgen_api.h"
#include "ida_star.h"

namespace fs = std::filesystem;
using MoveList = std::vector<Move>;

static bool ensurePdbsPresent() {
    std::vector<fs::path> missing;
    const auto dirPath = fs::path(PDB_DIR);
    const auto cornerPath = fs::path(PDB_DIR) / PDB_CORNER_FILENAME;
    const auto edgeFirstPath = fs::path(PDB_DIR) / PDB_EDGE_FIRST_FILENAME;
    const auto edgeSecondPath = fs::path(PDB_DIR) / PDB_EDGE_SECOND_FILENAME;

    if (!fs::exists(dirPath))           missing.push_back(dirPath.string() + " (directory)");
    if (!fs::exists(cornerPath))        missing.push_back(cornerPath.string());
    if (!fs::exists(edgeFirstPath))     missing.push_back(edgeFirstPath.string());
    if (!fs::exists(edgeSecondPath))    missing.push_back(edgeSecondPath.string());

    if (!missing.empty()) {
        std::cout << "Missing PDB assets:\n";
        for (auto& m : missing) std::cout << "  - " << m << '\n';
        std::cout << "Run `generate` first." << std::endl;
        return false;
    }
    return true;
}

void printMoveList(const std::string& start, const MoveList& moves) {
    std::cout << start;
    for (size_t i = 0; i < moves.size(); ++i) {
        if (i) std::cout << ' '; // add one space between tokens
        std::cout << MOVE_TO_STRING.at(moves[i]);
    }
    std::cout << '\n';
}

static void printHelp() {
    std::cout <<
R"(
┌─ Rubik's Cube CLI ────────────────────────────────────────────────┐
│ Commands                                                          │
│  help                    show this help                           │
│  generate                build pattern databases                  │
│  scramble <N>            generate an N-move scramble and solve    │
│  maxdepths               print max depths for piece groups        │
│  exit | quit | q         leave the program                        │
├───────────────────────────────────────────────────────────────────┤
│ Tips                                                              │
│  • Run `generate` once if PDBs are missing.                       │
│  • Commands are case-insensitive.                                 │
└───────────────────────────────────────────────────────────────────┘
)";
}

auto popAndGetFront = [](std::vector<std::string>& a) {
    if (a.empty()) return std::string{};
    auto front = std::move(a.front());
    a.erase(a.begin());
    return front;
};

int main() {
    printHelp();

    std::cout << "rcs> " << std::flush;  // first prompt
    for (std::string line; std::getline(std::cin, line); ) {
        if (line.empty()) { std::cout << "rcs> " << std::flush; continue; }

        std::stringstream ss(line);
        std::vector<std::string> words;
        for (std::string w; ss >> w; ) words.push_back(w);
        if (words.empty()) { std::cout << "rcs> " << std::flush; continue; }

        std::string w = popAndGetFront(words);
        if (w == "help") {
            printHelp();
        } else if (w == "generate") {
            std::cout << "Generating pattern databases...\n";
            run_pdbgen();
            std::cout << "Generation complete.\n";
        } else if (w == "scramble") {
            if (!ensurePdbsPresent()) {} // just fall through to prompt
            else if (!words.empty()) {
                IDAStar ida{};
                int n = std::stoi(popAndGetFront(words));
                if (n < 0) { std::cout << "Invalid N\n"; goto prompt; }
                MoveList scramble{}, solve{};
                ida.solveScramble(n, scramble, solve);
                printMoveList("Scramble: ", scramble);
                printMoveList("Solve:    ", solve);
                Cube c{};
                c.doMoves(scramble);
                c.doMoves(solve);
                if(!c.is_solved()) std::cout << "Solve is incorrect. Sorry for the inconvenience." << '\n';
            } else {
                std::cout << "Usage: scramble <N>\n";
            }
        } else if (w == "maxdepths") {
            std::cout << "Printing max depths...\n";
            printMaxDepths();
            std::cout << "Printing complete.\n";
        } else if (w == "exit" || w == "quit" || w == "q") {
            std::cout << "Bye!\n";
            break;
        } else {
            std::cout << "Invalid input.\n";
        }

        prompt:
        std::cout << "rcs> " << std::flush;
    }
    return 0;
}