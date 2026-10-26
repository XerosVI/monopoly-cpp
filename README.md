# Monopoly C++ (CLI Edition & AI Refactor)

A command-line C++ implementation of the classic Monopoly board game, featuring both the original high school codebase and a modern, modular C++17 refactor written with AI assistance (Claude).

---

## Project Overview & History

This repository showcases the evolution of a C++ terminal game across two distinct implementations:

1. **Original Version (`Monopoly.cpp`):** Created during high school as a personal project to learn C++ fundamentals, object-oriented programming, and terminal game loops in a single source file.
2. **Refactored Version (10-File Architecture):** Developed with AI assistance (Claude) as a modern C++17 code review and cleanup. This version reorganizes the single monolithic file into a clean, modular structure, addressing memory safety, robust input handling, and architectural design patterns.

---

## Evolution & Technical Improvements

| Feature / Aspect | Legacy High School Version (`Monopoly.cpp`) | AI-Refactored Version (C++17 Modular) |
| :--- | :--- | :--- |
| **Architecture** | Single monolithic `.cpp` file | Modular structure split across 10 header & implementation files |
| **Memory Safety** | Raw pointers (`Giocatore*`) causing dangling references on bankruptcy | Index-based ownership (`std::optional<std::size_t>`) |
| **Input Handling** | Basic `std::cin` streams prone to buffer skips and infinite loops | Dedicated `input::` namespace using `std::getline` and strict type validation |
| **Randomness** | C-style `rand()` and `srand(time(0))` | Modern `<random>` engine (`std::mt19937`) for uniform distribution |
| **Board Model** | Loose string matching for special tiles | Strongly typed enums (`TipoCasella`, `Colore`) and factory constructors |
| **Asset Liquidation** | Player vector erasure mid-loop without resetting owned tiles | Safe `inGioco` state flags and automatic property resets back to the bank |

---

## File Structure

```text
.
├── Casella.h        # Tile data structure, types, and factory functions
├── Giocatore.h      # Lightweight player state representation
├── Gioco.h          # Core game loop and manager header
├── Gioco.cpp        # Turn actions, property transactions, cards, and bankruptcy logic
├── Input.h          # Safe input module interface
├── Input.cpp        # Safe line-by-line CLI parsing routines
├── Tabellone.h      # Board state manager header
├── Tabellone.cpp    # Board setup, color-group evaluations, and display renderer
├── main.cpp         # Entry point with top-level error handling
├── Monopoly.cpp     # Original single-file high school code
└── Makefile         # Build script for modern C++ compilation
```

---

## Compilation and Execution

### Requirements

- A C++17 compliant compiler (`g++` 7+, `clang++` 5+, or MSVC).
- `make` utility (optional).

### Building the AI-Refactored Modular Version

Using `make`:
```bash
make
./monopoly
```

Clean build artifacts:
```bash
make clean
```

Manual compilation with `g++`:
```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp Gioco.cpp Tabellone.cpp Input.cpp -o monopoly
./monopoly
```

### Compiling the Legacy High School Version

```bash
g++ -O2 Monopoly.cpp -o monopoly_legacy
./monopoly_legacy
```

---

## How to Play

1. Run either executable.
2. Enter the number of players (2 to 8).
3. Assign custom player names and select distinct tokens (`Auto`, `Cappello`, `Scarpa`, etc.).
4. Take turns pressing `Enter` to roll the dice and move around the board.
5. Answer prompt questions (`s`/`n`) to buy properties or build houses/hotels when landing on eligible spaces.
6. The game continues until only one solvent player remains.

---

## License

Distributed under the [MIT License](LICENSE).