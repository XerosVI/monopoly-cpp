# Monopoly C++ (Legacy High School Edition)

A single-file, command-line implementation of the classic Monopoly board game written in C++ as a high school learning project.

---

## About This Project

This program (`Monopoly.cpp`) was created during high school to experiment with basic programming concepts in C++, object-oriented programming, and game logic implementation. 

It implements a simplified CLI version of Monopoly using standard C++ features (`std::vector`, `std::string`, `rand()`, and standard console input/output via `std::cin` and `std::cout`).

---

## Features

- **Single-File Architecture:** Entire game logic, player data, board configuration, and main game loop contained within `Monopoly.cpp`.
- **Classic Italian Monopoly Board:** Features standard properties like *Vicolo Corto*, *Parco della Vittoria*, *Stazioni*, and *Servizi*.
- **Core Game Rules:**
  - Dice rolling (`rand() % 6`) and passing "Via" to receive $100.
  - Property purchasing and basic rent transactions between players.
  - Group ownership checks allowing players to build houses and hotels.
  - Chance cards (*Probabilità*) and basic Jail system logic.
  - Player bankruptcy check and turn-based elimination loop.

---

## Compilation and Execution

### Requirements

- Any C++ compiler supporting C++11 or higher (e.g., `g++`, `clang++`, or MSVC).

### How to Compile & Run

**Using GCC (`g++`):**
```bash
g++ -O2 Monopoly.cpp -o monopoly_legacy
./monopoly_legacy
```

**Using Clang (`clang++`):**
```bash
clang++ -O2 Monopoly.cpp -o monopoly_legacy
./monopoly_legacy
```

---

## How to Play

1. Run the compiled executable.
2. Enter the number of players (between 2 and 8).
3. Provide names and select distinct tokens (`Auto`, `Cappello`, `Scarpa`, etc.) for each player.
4. Take turns pressing `Enter` to roll the dice and navigate around the board.
5. Answer prompt questions (`s`/`n`) to buy properties or build houses/hotels when landing on valid spaces.
6. The game continues until only one solvent player remains.

---

## Historical Context & Note

This version represents an early stage of learning C++ fundamentals. As a high school project, it uses basic C-style pseudo-random number generation (`rand()`, `srand(time(0))`) and standard `cin` input streams. 

---

## License

Distributed under the [MIT License](LICENSE).