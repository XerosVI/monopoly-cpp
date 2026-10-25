#pragma once
#include <cstddef>
#include <optional>
#include <random>
#include <vector>
#include "Giocatore.h"
#include "Tabellone.h"

class Gioco {
public:
    Gioco();
    void configura();  // chiede numero giocatori, nomi e pedine
    void esegui();     // loop di gioco fino al vincitore

private:
    void turno(std::size_t i);
    bool gestisciPrigione(std::size_t i);  // true se il giocatore puo' giocare il turno
    void muovi(std::size_t i, int passi);
    void gestisciCasella(std::size_t i, int dadi);
    void proponiAcquisto(std::size_t i, Casella& casella);
    void pagaAffitto(std::size_t i, const Casella& casella, int dadi);
    void proponiCostruzione(std::size_t i);
    void costruisci(std::size_t i, Casella& casella);
    void pescaCarta(std::size_t i, const Casella& casella);
    void mandaInPrigione(std::size_t i);

    void addebita(std::size_t i, int importo, std::optional<std::size_t> beneficiario = std::nullopt);
    void controllaBancarotta(std::size_t i);
    void stampaSaldo(std::size_t i) const;
    int calcolaAffitto(const Casella& casella, int dadi) const;
    int lanciaDado();
    std::size_t giocatoriInGioco() const;

    Tabellone tabellone_;
    std::vector<Giocatore> giocatori_;
    std::mt19937 rng_;
};
