#include "Tabellone.h"
#include <iostream>

Tabellone::Tabellone() {
    using T = TipoCasella;
    using C = Colore;
    caselle_ = {
        Casella::speciale("Via", T::Via),
        Casella::terreno("Vicolo Corto", 60, 2, C::Marrone),
        Casella::speciale("Probabilita'", T::Probabilita),
        Casella::terreno("Vicolo Stretto", 60, 4, C::Marrone),
        Casella::tassa("Tassa Patrimoniale", 200),
        Casella::stazione("Stazione Sud"),
        Casella::terreno("Bastioni Gran Sasso", 100, 6, C::Azzurro),
        Casella::speciale("Imprevisti", T::Imprevisti),
        Casella::terreno("Viale Monterosa", 100, 6, C::Azzurro),
        Casella::terreno("Viale Vesuvio", 120, 8, C::Azzurro),
        Casella::speciale("Prigione", T::Prigione),
        Casella::terreno("Via Accademia", 140, 10, C::Rosa),
        Casella::servizio("Societa' Elettrica"),
        Casella::terreno("Corso Ateneo", 140, 10, C::Rosa),
        Casella::terreno("Piazza Universita'", 160, 12, C::Rosa),
        Casella::stazione("Stazione Ovest"),
        Casella::terreno("Via Verdi", 180, 14, C::Arancione),
        Casella::speciale("Probabilita'", T::Probabilita),
        Casella::terreno("Corso Raffaello", 180, 14, C::Arancione),
        Casella::terreno("Piazza Dante", 200, 16, C::Arancione),
        Casella::speciale("Parcheggio Gratuito", T::Parcheggio),
        Casella::terreno("Via Marco Polo", 220, 18, C::Rosso),
        Casella::speciale("Imprevisti", T::Imprevisti),
        Casella::terreno("Corso Magellano", 220, 18, C::Rosso),
        Casella::terreno("Largo Colombo", 240, 20, C::Rosso),
        Casella::stazione("Stazione Nord"),
        Casella::terreno("Viale Costantino", 260, 22, C::Giallo),
        Casella::terreno("Viale Traiano", 260, 22, C::Giallo),
        Casella::servizio("Societa' Acqua Potabile"),
        Casella::terreno("Piazza Giulio Cesare", 280, 24, C::Giallo),
        Casella::speciale("Vai in Prigione", T::VaiInPrigione),
        Casella::terreno("Via Roma", 300, 26, C::Verde),
        Casella::terreno("Corso Impero", 300, 26, C::Verde),
        Casella::speciale("Probabilita'", T::Probabilita),
        Casella::terreno("Largo Augusto", 320, 28, C::Verde),
        Casella::stazione("Stazione Est"),
        Casella::speciale("Imprevisti", T::Imprevisti),
        Casella::terreno("Viale dei Giardini", 350, 35, C::Blu),
        Casella::tassa("Tassa di Lusso", 100),
        Casella::terreno("Parco della Vittoria", 400, 50, C::Blu),
    };
    for (std::size_t i = 0; i < caselle_.size(); ++i)
        if (caselle_[i].tipo == T::Prigione) posPrigione_ = i;
}

bool Tabellone::possiedeGruppo(std::size_t giocatore, Colore colore) const {
    for (const Casella& c : caselle_)
        if (c.colore == colore && c.proprietario != giocatore) return false;
    return true;
}

int Tabellone::contaPossedute(std::size_t giocatore, TipoCasella tipo) const {
    int n = 0;
    for (const Casella& c : caselle_)
        if (c.tipo == tipo && c.proprietario == giocatore) ++n;
    return n;
}

void Tabellone::liberaProprieta(std::size_t giocatore) {
    for (Casella& c : caselle_)
        if (c.proprietario == giocatore) c.liberaProprieta();
}

void Tabellone::stampa(const std::vector<Giocatore>& giocatori) const {
    for (std::size_t i = 0; i < caselle_.size(); ++i) {
        std::cout << '[' << caselle_[i].nome;
        for (const Giocatore& g : giocatori)
            if (g.inGioco && g.posizione == i) std::cout << ", " << g.pedina;
        std::cout << "] ";
    }
    std::cout << '\n';
}
