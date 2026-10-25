#pragma once
#include <cstddef>
#include <vector>
#include "Casella.h"
#include "Giocatore.h"

class Tabellone {
public:
    Tabellone();

    std::size_t dimensione() const { return caselle_.size(); }
    std::size_t posizionePrigione() const { return posPrigione_; }

    Casella& operator[](std::size_t i) { return caselle_[i]; }
    const Casella& operator[](std::size_t i) const { return caselle_[i]; }

    bool possiedeGruppo(std::size_t giocatore, Colore colore) const;
    int contaPossedute(std::size_t giocatore, TipoCasella tipo) const;
    void liberaProprieta(std::size_t giocatore);

    // [Casella, Pedina, Pedina, ...] per ogni casella
    void stampa(const std::vector<Giocatore>& giocatori) const;

private:
    std::vector<Casella> caselle_;
    std::size_t posPrigione_ = 0;
};
