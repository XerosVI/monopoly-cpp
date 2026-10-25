# Monopoly C++ (CLI Edition)

A modular, object-oriented command-line implementation of the classic Monopoly board game written in C++17.

---

## Overview

This repository contains a full C++ terminal implementation of Monopoly using standard rules, property groups, color sets, and automated turn management. It features safe memory management patterns, robust input handling, and a clean separation of concerns across standard modern C++ modules.

---

## Key Features

- **Modern C++17:** Uses modern standard library features including `std::optional`, `std::string_view`, and uniform pseudo-random number generators (`std::mt19937`).
- **Safe Memory & Ownership Model:** Replaces fragile raw pointers with safe index-based ownership markers (`std::optional<std::size_t>`). Eliminates dangling pointers and memory safety issues during player bankruptcy.
- **Robust Input Module:** Safe line-by-line input processing (`std::getline`) with parsing validation (`std::stoi`) preventing infinite loop bugs on invalid input.
- **Complete Board & Game Logic:**
  - Classic Italian Monopoly board layout (*Vicolo Corto*, *Parco della Vittoria*, *Stazioni*, *Servizi*).
  - Group ownership checks required for house and hotel construction.
  - Variable rent calculations for Utilities and Railway stations.
  - Jail system with turn decrementing and bail payments.
  - Automatic liquidation of bankrupt players' properties back to the bank.

---

## File Structure

| File | Description |
| :--- | :--- |
| `main.cpp` | Program entry point and top-level error handling. |
| `Gioco.h` / `Gioco.cpp` | Core game manager: handles turn loops, rent transactions, cards, and bankruptcy. |
| `Tabellone.h` / `Tabellone.cpp` | Board state: initializes tiles, evaluates color sets, and renders board overview. |
| `Casella.h` | Header struct representing board spaces with expressive factory constructors. |
| `Giocatore.h` | Lightweight player state structure (balance, token, position, jail status). |
| `Input.h` / `Input.cpp` | Safe console input reading routines inside dedicated namespaces. |
| `Makefile` | Build script for easy compilation using GCC/Clang. |

---

## Compilation and Execution

### Requirements

- A C++17 compliant compiler (`g++` 7+, `clang++` 5+, or MSVC).
- `make` utility (optional, for Linux/macOS/WSL).

### Build Instructions

**Using Make:**
```bash
make
./monopoly
```

**Clean build artifacts:**
```bash
make clean
```

**Manual Compilation (`g++`):**
```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp Gioco.cpp Tabellone.cpp Input.cpp -o monopoly
./monopoly
```

---

## License

Distributed under the [MIT License](LICENSE).