#include "Gioco.h"
#include <algorithm>
#include <iostream>
#include <string_view>
#include "Input.h"

namespace {

constexpr int kBonusVia = 100;
constexpr int kCostoCasa = 50;
constexpr int kCostoAlbergo = 200;
constexpr int kCostoUscitaPrigione = 50;
constexpr int kTurniPrigione = 3;
constexpr int kMinGiocatori = 2;
constexpr int kMaxGiocatori = 8;

enum class Effetto { Nessuno, AvanzaAlVia, VaiInPrigione };

struct Carta {
    std::string_view testo;
    int variazioneSaldo;
    Effetto effetto;
};

constexpr Carta kCarte[] = {
    {"Avanza al Via (Raccogli $100)", +100, Effetto::AvanzaAlVia},
    {"Paga $50", -50, Effetto::Nessuno},
    {"Raccogli $50", +50, Effetto::Nessuno},
    {"Paga $100", -100, Effetto::Nessuno},
    {"Vai in prigione!", 0, Effetto::VaiInPrigione},
};

const std::vector<std::string> kPedine = {
    "Auto", "Cappello", "Scarpa", "Cane", "Carriola", "Battello", "Ferro da stiro", "Ditale"};

}  // namespace

Gioco::Gioco() : rng_(std::random_device{}()) {}

// ---------------------------------------------------------------- setup

void Gioco::configura() {
    const int n = input::intero("Inserisci il numero di giocatori (" + std::to_string(kMinGiocatori) +
                                "-" + std::to_string(kMaxGiocatori) + "): ",
                                kMinGiocatori, kMaxGiocatori);
    std::vector<std::string> pedine = kPedine;

    for (int i = 1; i <= n; ++i) {
        Giocatore g;
        g.nome = input::testo("Inserisci il nome per il giocatore " + std::to_string(i) + ": ");

        std::cout << "Pedine disponibili: ";
        for (std::size_t j = 0; j < pedine.size(); ++j)
            std::cout << j + 1 << ". " << pedine[j] << "  ";
        std::cout << '\n';

        const int scelta = input::intero("Scegli una pedina: ", 1, static_cast<int>(pedine.size()));
        g.pedina = pedine[scelta - 1];
        pedine.erase(pedine.begin() + (scelta - 1));
        giocatori_.push_back(std::move(g));
    }
}

// ---------------------------------------------------------------- loop

void Gioco::esegui() {
    while (giocatoriInGioco() > 1) {
        for (std::size_t i = 0; i < giocatori_.size() && giocatoriInGioco() > 1; ++i) {
            if (!giocatori_[i].inGioco) continue;
            turno(i);
            controllaBancarotta(i);
        }
    }

    for (const Giocatore& g : giocatori_)
        if (g.inGioco) {
            std::cout << "Gioco finito! Il vincitore e' " << g.nome << " con $" << g.saldo << ".\n";
            return;
        }
    std::cout << "Gioco finito! Nessun vincitore.\n";
}

void Gioco::turno(std::size_t i) {
    if (giocatori_[i].turniPrigione > 0 && !gestisciPrigione(i)) return;

    std::cout << "\nTurno di " << giocatori_[i].nome << ". Saldo attuale: $" << giocatori_[i].saldo << '\n';
    input::attendiInvio("Premi Invio per tirare i dadi...");

    const int d1 = lanciaDado();
    const int d2 = lanciaDado();
    std::cout << giocatori_[i].nome << " ha tirato " << d1 << " e " << d2
              << " per un totale di " << d1 + d2 << '\n';

    muovi(i, d1 + d2);
    std::cout << giocatori_[i].nome << " e' atterrato su "
              << tabellone_[giocatori_[i].posizione].nome << '\n';

    gestisciCasella(i, d1 + d2);
    if (giocatori_[i].saldo >= 0) proponiCostruzione(i);

    tabellone_.stampa(giocatori_);
}

bool Gioco::gestisciPrigione(std::size_t i) {
    Giocatore& g = giocatori_[i];
    std::cout << g.nome << " e' in prigione per altri " << g.turniPrigione << " turno(i).\n";

    if (g.saldo >= kCostoUscitaPrigione &&
        input::siNo("Vuoi pagare $" + std::to_string(kCostoUscitaPrigione) + " per uscire di prigione?")) {
        addebita(i, kCostoUscitaPrigione);
        g.turniPrigione = 0;
        std::cout << g.nome << " ha pagato per uscire di prigione.\n";
        return true;
    }
    --g.turniPrigione;
    return false;
}

// ---------------------------------------------------------------- azioni

void Gioco::muovi(std::size_t i, int passi) {
    Giocatore& g = giocatori_[i];
    std::size_t nuova = g.posizione + static_cast<std::size_t>(passi);
    if (nuova >= tabellone_.dimensione()) {
        g.saldo += kBonusVia;
        std::cout << g.nome << " ha raccolto $" << kBonusVia << " passando dal Via.\n";
        nuova %= tabellone_.dimensione();
    }
    g.posizione = nuova;
}

void Gioco::gestisciCasella(std::size_t i, int dadi) {
    Giocatore& g = giocatori_[i];
    Casella& c = tabellone_[g.posizione];

    switch (c.tipo) {
        case TipoCasella::Via:
        case TipoCasella::Prigione:
            break;
        case TipoCasella::Parcheggio:
            std::cout << g.nome << " si riposa nel Parcheggio Gratuito.\n";
            break;
        case TipoCasella::Tassa:
            std::cout << g.nome << " deve pagare " << c.nome << " di $" << c.affitto << ".\n";
            addebita(i, c.affitto);
            break;
        case TipoCasella::Probabilita:
        case TipoCasella::Imprevisti:
            pescaCarta(i, c);
            break;
        case TipoCasella::VaiInPrigione:
            std::cout << g.nome << " e' stato mandato in prigione per " << kTurniPrigione << " turni.\n";
            mandaInPrigione(i);
            break;
        case TipoCasella::Terreno:
        case TipoCasella::Stazione:
        case TipoCasella::Servizio:
            if (!c.proprietario)
                proponiAcquisto(i, c);
            else if (*c.proprietario != i)
                pagaAffitto(i, c, dadi);
            break;
    }
}

void Gioco::proponiAcquisto(std::size_t i, Casella& casella) {
    Giocatore& g = giocatori_[i];
    if (g.saldo < casella.costo) {
        std::cout << g.nome << " non ha abbastanza soldi per comprare " << casella.nome << ".\n";
        return;
    }
    if (!input::siNo("Vuoi comprare " + casella.nome + " per $" + std::to_string(casella.costo) + "?")) {
        std::cout << g.nome << " ha scelto di non comprare " << casella.nome << ".\n";
        return;
    }
    g.saldo -= casella.costo;
    casella.proprietario = i;
    std::cout << g.nome << " ha comprato " << casella.nome << " per $" << casella.costo << '\n';
    stampaSaldo(i);
}

int Gioco::calcolaAffitto(const Casella& c, int dadi) const {
    const std::size_t prop = *c.proprietario;
    switch (c.tipo) {
        case TipoCasella::Terreno:
            return c.affitto * c.moltiplicatoreEdifici();
        case TipoCasella::Stazione:
            return c.affitto * tabellone_.contaPossedute(prop, TipoCasella::Stazione);
        case TipoCasella::Servizio:
            return (tabellone_.contaPossedute(prop, TipoCasella::Servizio) == 2 ? 10 : 4) * dadi;
        default:
            return 0;
    }
}

void Gioco::pagaAffitto(std::size_t i, const Casella& casella, int dadi) {
    const std::size_t prop = *casella.proprietario;
    const int affitto = calcolaAffitto(casella, dadi);
    addebita(i, affitto, prop);
    std::cout << giocatori_[i].nome << " ha pagato $" << affitto << " di affitto a "
              << giocatori_[prop].nome << '\n';
    stampaSaldo(i);
    stampaSaldo(prop);
}

void Gioco::proponiCostruzione(std::size_t i) {
    Casella& c = tabellone_[giocatori_[i].posizione];
    if (!c.costruibile() || c.proprietario != i || c.albergo) return;
    if (!tabellone_.possiedeGruppo(i, c.colore)) return;

    if (input::siNo("Vuoi costruire una casa o un albergo su " + c.nome + "?"))
        costruisci(i, c);
}

void Gioco::costruisci(std::size_t i, Casella& casella) {
    Giocatore& g = giocatori_[i];
    const bool albergo = casella.numCase == 4;
    const int costo = albergo ? kCostoAlbergo : kCostoCasa;

    if (g.saldo < costo) {
        std::cout << g.nome << " non ha abbastanza soldi per costruire ($" << costo << ").\n";
        return;
    }
    g.saldo -= costo;
    if (albergo) {
        casella.albergo = true;
        std::cout << g.nome << " ha costruito un albergo su " << casella.nome << '\n';
    } else {
        ++casella.numCase;
        std::cout << g.nome << " ha costruito una casa su " << casella.nome << '\n';
    }
    stampaSaldo(i);
}

void Gioco::pescaCarta(std::size_t i, const Casella& casella) {
    std::uniform_int_distribution<std::size_t> dist(0, std::size(kCarte) - 1);
    const Carta& carta = kCarte[dist(rng_)];
    Giocatore& g = giocatori_[i];

    std::cout << casella.nome << ": " << carta.testo << '\n';
    if (carta.variazioneSaldo > 0) g.saldo += carta.variazioneSaldo;
    else if (carta.variazioneSaldo < 0) addebita(i, -carta.variazioneSaldo);

    switch (carta.effetto) {
        case Effetto::AvanzaAlVia: g.posizione = 0; break;
        case Effetto::VaiInPrigione: mandaInPrigione(i); break;
        case Effetto::Nessuno: break;
    }
    stampaSaldo(i);
}

void Gioco::mandaInPrigione(std::size_t i) {
    giocatori_[i].posizione = tabellone_.posizionePrigione();
    giocatori_[i].turniPrigione = kTurniPrigione;
}

// ---------------------------------------------------------------- utilita'

// Il beneficiario riceve al massimo quanto il debitore possiede davvero.
void Gioco::addebita(std::size_t i, int importo, std::optional<std::size_t> beneficiario) {
    Giocatore& g = giocatori_[i];
    if (beneficiario)
        giocatori_[*beneficiario].saldo += std::clamp(g.saldo, 0, importo);
    g.saldo -= importo;
}

void Gioco::controllaBancarotta(std::size_t i) {
    Giocatore& g = giocatori_[i];
    if (g.saldo >= 0) return;
    std::cout << g.nome << " e' in bancarotta ed e' stato eliminato dal gioco.\n";
    g.inGioco = false;
    tabellone_.liberaProprieta(i);  // le proprieta' tornano alla banca
}

void Gioco::stampaSaldo(std::size_t i) const {
    std::cout << giocatori_[i].nome << " ora ha $" << giocatori_[i].saldo << " rimanenti.\n";
}

int Gioco::lanciaDado() {
    return std::uniform_int_distribution<int>(1, 6)(rng_);
}

std::size_t Gioco::giocatoriInGioco() const {
    return static_cast<std::size_t>(
        std::count_if(giocatori_.begin(), giocatori_.end(), [](const Giocatore& g) { return g.inGioco; }));
}
