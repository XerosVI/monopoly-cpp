#pragma once
#include <cstddef>
#include <string>

// Dati di un giocatore. Le proprieta' non sono tenute qui: ogni Casella
// conosce l'indice del suo proprietario (nessun puntatore che possa "penzolare").
struct Giocatore {
    std::string nome;
    std::string pedina;
    std::size_t posizione = 0;
    int saldo = 1500;
    int turniPrigione = 0;
    bool inGioco = true;
};
