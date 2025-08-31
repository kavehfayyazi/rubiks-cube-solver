
#include <iostream>
#include <sstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "solve.h"
#include "move.h"
#include "cube.h"
#include "maxdepths_api.h"
#include "pdbgen_api.h"

namespace fs = std::filesystem;
using MoveList = std::vector<Move>;

struct PdbPaths {
    fs::path dir  = fs::path(PDB_DIR);
    fs::path c    = fs::path(PDB_DIR) / PDB_CORNER_FILENAME;
    fs::path e1   = fs::path(PDB_DIR) / PDB_EDGE_FIRST_FILENAME;
    fs::path e2   = fs::path(PDB_DIR) / PDB_EDGE_SECOND_FILENAME;
};

static std::vector<fs::path> missingPdbs(const PdbPaths& p) {
    std::vector<fs::path> miss;
    if (!fs::exists(p.dir))            miss.push_back(p.dir.string() + " (directory)");
    if (!fs::exists(p.c))              miss.push_back(p.c);
    if (!fs::exists(p.e1))             miss.push_back(p.e1);
    if (!fs::exists(p.e2))             miss.push_back(p.e2);
    return miss;
}

static bool ensurePdbsPresent(bool printWhy = true) {
    PdbPaths p;
    auto miss = missingPdbs(p);
    if (!miss.empty()) {
        if (printWhy) {
            std::cout << "Missing PDB assets:\n";
            for (auto& m : miss) std::cout << "  - " << m << '\n';
            std::cout << "Run `generate` first." << std::endl;
        }
        return false;
    }
    return true;
}

std::string moveListToString(const std::string& start, const MoveList& moves) {
    std::ostringstream out;
    out << start;
    for (size_t i = 0; i < moves.size(); ++i) {
        out << MOVE_TO_STRING.at(moves[i]);
        if (i + 1 < moves.size()) out << ' ';
    }
    return out.str();
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
            if (!ensurePdbsPresent()) {
                // ensurePdbsPresent prints why; just fall through to prompt
            } else if (!words.empty()) {
                int n = std::stoi(popAndGetFront(words));
                if (n < 0) { std::cout << "Invalid N\n"; goto prompt; }
                MoveList scramble{}, solve{};
                solveScramble(n, scramble, solve);
                std::cout << moveListToString("Scramble: ", scramble) << '\n';
                std::cout << moveListToString("Solve:    ", solve) << '\n';
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