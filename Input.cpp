#include "Input.h"
#include <iostream>
#include <stdexcept>

namespace {
std::string leggiRiga() {
    std::string riga;
    if (!std::getline(std::cin, riga))
        throw std::runtime_error("Input terminato.");
    return riga;
}
}

namespace input {

std::string testo(const std::string& domanda) {
    while (true) {
        std::cout << domanda;
        std::string riga = leggiRiga();
        if (!riga.empty()) return riga;
    }
}

int intero(const std::string& domanda, int min, int max) {
    while (true) {
        std::cout << domanda;
        try {
            std::size_t pos = 0;
            const std::string riga = leggiRiga();
            const int v = std::stoi(riga, &pos);
            if (pos == riga.size() && v >= min && v <= max) return v;
        } catch (const std::logic_error&) {  // stoi: non numerico / fuori range
        }
        std::cout << "Valore non valido (" << min << "-" << max << ").\n";
    }
}

bool siNo(const std::string& domanda) {
    while (true) {
        std::cout << domanda << " (s/n): ";
        const std::string riga = leggiRiga();
        if (!riga.empty()) {
            const char c = static_cast<char>(std::tolower(static_cast<unsigned char>(riga[0])));
            if (c == 's') return true;
            if (c == 'n') return false;
        }
    }
}

void attendiInvio(const std::string& messaggio) {
    std::cout << messaggio;
    leggiRiga();
}

}  // namespace input
