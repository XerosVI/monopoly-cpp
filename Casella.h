#pragma once
#include <cstddef>
#include <optional>
#include <string>

enum class TipoCasella {
    Via, Terreno, Stazione, Servizio, Probabilita, Imprevisti,
    Tassa, Prigione, VaiInPrigione, Parcheggio
};

enum class Colore {
    Nessuno, Marrone, Azzurro, Rosa, Arancione, Rosso, Giallo, Verde, Blu
};

struct Casella {
    std::string nome;
    TipoCasella tipo = TipoCasella::Via;
    int costo = 0;      // prezzo d'acquisto
    int affitto = 0;    // affitto base (per le Tasse: importo dovuto)
    Colore colore = Colore::Nessuno;
    int numCase = 0;    // 0..4
    bool albergo = false;
    std::optional<std::size_t> proprietario;

    bool acquistabile() const {
        return tipo == TipoCasella::Terreno || tipo == TipoCasella::Stazione ||
               tipo == TipoCasella::Servizio;
    }
    bool costruibile() const { return tipo == TipoCasella::Terreno; }
    int moltiplicatoreEdifici() const { return albergo ? 10 : numCase + 1; }

    void liberaProprieta() {
        proprietario.reset();
        numCase = 0;
        albergo = false;
    }

    // Costruttori "con nome": rendono leggibile la definizione del tabellone.
    static Casella terreno(std::string nome, int costo, int affitto, Colore colore) {
        Casella c; c.nome = std::move(nome); c.tipo = TipoCasella::Terreno;
        c.costo = costo; c.affitto = affitto; c.colore = colore; return c;
    }
    static Casella stazione(std::string nome) {
        Casella c; c.nome = std::move(nome); c.tipo = TipoCasella::Stazione;
        c.costo = 200; c.affitto = 25; return c;
    }
    static Casella servizio(std::string nome) {
        Casella c; c.nome = std::move(nome); c.tipo = TipoCasella::Servizio;
        c.costo = 150; return c;
    }
    static Casella tassa(std::string nome, int importo) {
        Casella c; c.nome = std::move(nome); c.tipo = TipoCasella::Tassa;
        c.affitto = importo; return c;
    }
    static Casella speciale(std::string nome, TipoCasella tipo) {
        Casella c; c.nome = std::move(nome); c.tipo = tipo; return c;
    }
};
