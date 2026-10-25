// Monopoly a riga di comando (nessuna interfaccia grafica).
#include <exception>
#include <iostream>
#include "Gioco.h"

int main() {
    try {
        Gioco gioco;
        gioco.configura();
        gioco.esegui();
    } catch (const std::exception& e) {
        std::cerr << "\nErrore: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
