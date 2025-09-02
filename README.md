# Rubiks-Cube Solver

A fast, modern C++20 Rubik's Cube solver centered on IDA* search and compact pattern-database (PDB) heuristics. It ships with a tiny CLI (`rcs>`) for scrambling/solving and tooling to generate PDBs locally.

## TL;DR

```console
# Run interactive CLI
./build/tools/cli/cli
rcs> generate
Generating pattern databases...
Generation complete.
rcs> scramble 10
Scramble: L U2 B R B' R2 L2 U2 L B
Solve:    B' L' U2 R2 L2 B R' B' U2 L'
```

## Features

* **IDA\*** with a multi-level heuristic: corners + two 6-edge sets.
* **Compact encodings** for corners and edges (rank permutations & combinations)
* **Deterministic** scramble/solve flows; reproducible runs.
* **Simple CLI** (`rcs>`) for ease of use.
* **No external runtime dependencies** — only a C++ toolchain & CMake.

## Quick Start

### Prereqs

* CMake >= 3.21
* A C++20 compiler

### Build and Run the CLI

```bash
# from repo root
mkdir build
cmake -S . -B build
cmake --build build

mkdir pdb # if pdb/ does not exist at root
./build/tools/cli/cli
```

#### Commands (subject to change):

* `help` — list commands
* `generate` — build pattern databases
* `scramble <N>` — generate N-move scramble and solve
* `maxdepths` — print max depths for piece groups
* `exit | quit | q` — exit

### Generate pattern databases

PDBs are not committed. Generate them once locally in the `rcs>` CLI using the `generate` command. (This step can be slow—on the order of tens of minutes depending on hardware.)

## Project Structure

```
.
├── CMakeLists.txt
├── include/            # public headers
├── src/                # cube, encoders, solver, PDB handlers
│   ├── cube/           # state, moves, encoding helpers 
│   └── ida_star/       # IDA* solver, heuristics, PDB access 
├── tools/
│   ├── pdbgen/         # PDB generator
│   ├── maxdepths/      # print max depths of corner/edge piece groups
│   └── cli/            # interactive CLI 
├── tests/              # unit tests (Catch2)
├── pdb/                # generated PDBs (gitignored)
└── README.md
```

## Testing

This project uses **CTest** and **Catch2**.

```bash
cd build
ctest --output-on-failure
```

## Implementation Notes

* **IDA\*** iteratively deepens `g + h`, combining a corner PDB with two 6-edge PDBs; a multi-level check exits early when `g + h` exceeds the current bound.
* **Encodings**: permutations using Lehmer code; combinations via the combinatorial number system.
* **Two 6-edge PDBS** substantially reduce the search space while preserving a strong heuristic.
* **Precomputed** move and inverse tables for speed.

## Pattern Databases


**Encoding.** Each corner piece group and the two 6-edge piece groups are represented as permutation/combination indices without repetition (injection).

**Generation.** PDBs are built via BFS from the solved state, recording the move depth at first visit. Values are stored in `.pdb` files; with 4-bit packing, two depths can be stored per byte when depths are ≤ 15. Note: Different choices of the 6-edge groups can have different max depths (some reach 15). You can inspect these with the maxdepths command in the CLI. Generation and max-depth scans may take a while on a first run.

## Contributing

1. **Fork** this repository.

2. **Clone** your fork locally:

    ```bash
    git clone https://github.com/<your-username>/rubiks-cube-solver.git
    cd rubiks-cube-solver
    ```

3. **Create** a new branch:

    ```bash
    git checkout -b feature/your-feature
    ```

4. **Commit** your changes:

    ```bash
    git commit -m "Add feature-name."
    ```

5. **Push** to the branch

    ```bash
    git push origin feature/feature-name
    ```

6. **Open** a pull request.

## License

MIT — see [LICENSE](LICENSE).